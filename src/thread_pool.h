//
// Created by zsc on 2023/11/8.
//

#ifndef KITE_THREAD_POOL_H
#define KITE_THREAD_POOL_H
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <unistd.h>
#include <utility>
#include <vector>

template <typename T> class safe_queue {
private:
  std::queue<T> task_queue;
  std::mutex task_mutex;

public:
  safe_queue() = default;
  safe_queue(safe_queue &&sq) noexcept {};
  ~safe_queue() = default;
  bool empty() {
    std::unique_lock<std::mutex> lock(task_mutex);
    return task_queue.empty();
  }

  int size() {
    std::unique_lock<std::mutex> lock(task_mutex);
    return task_queue.size();
  }

  void enqueue(T &t) {
    std::unique_lock<std::mutex> lock(task_mutex);
    task_queue.emplace(t);
  }

  bool dequeue(T &t) {
    std::unique_lock<std::mutex> lock(task_mutex);
    if (task_queue.empty()) {
      return false;
    }
    t = std::move(task_queue.front());
    task_queue.pop();
    return true;
  }
};

class thread_pool {
private:
  bool m_shutdown;
  safe_queue<std::function<void()>> m_queue;
  std::vector<std::thread> m_threads;
  std::mutex m_conditional_mutex;
  std::condition_variable m_conditional_lock;

  class thread_worker {
  private:
    int m_id;
    thread_pool *m_pool;

  public:
    thread_worker(thread_pool *pool, const int id) : m_pool(pool), m_id(id){};

    void operator()() {
      std::function<void()> func;
      bool dequeued;
      while (!m_pool->m_shutdown) {
        {
          std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex);
          if (m_pool->m_queue.empty()) {
            m_pool->m_conditional_lock.wait(lock);
          }
          dequeued = m_pool->m_queue.dequeue(func);
        }
        if (dequeued) {
          func();
        }
      }
    };
  };

public:
  explicit thread_pool(const int n_threads = 4)
      : m_threads(std::vector<std::thread>(n_threads)), m_shutdown(false) {}
  thread_pool(const thread_pool &) = delete;
  thread_pool(thread_pool &&) = delete;
  thread_pool &operator=(const thread_pool &) = delete;
  thread_pool &operator=(thread_pool &&) = delete;

  void init() {
    for (int i = 0; i < m_threads.size(); ++i) {
      m_threads.at(i) = std::thread(thread_worker(this, i));
    }
  }

  void shutdown() {
    while (!m_queue.empty()) {
      sleep(3);
    }
    m_shutdown = true;
    m_conditional_lock.notify_all();
    for (auto &m_thread : m_threads) {
      if (m_thread.joinable()) {
        m_thread.join();
      }
    }
  }

  template <typename F, typename... Args>
  auto submit(F &&f, Args &&...args) -> std::future<decltype((f(args...)))> {
    std::function<decltype(f(args...))()> func =
        std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    auto task_ptr =
        std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

    std::function<void()> wrapper_func = [task_ptr]() { (*task_ptr)(); };

    m_queue.enqueue(wrapper_func);

    m_conditional_lock.notify_one();

    return task_ptr->get_future();
  }
};
#endif // KITE_THREAD_POOL_H
