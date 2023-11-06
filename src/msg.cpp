//
// Created by zsc on 2023/11/6.
//

#include "msg.h"
#include <iomanip>
void msg::info(const std::string &str) {
  time_t now = time(nullptr);
  tm *tm_t = localtime(&now);
  std::cout << "\033[32m [" << std::setw(2) << std::setfill('0')
            << tm_t->tm_hour << ":" << std::setw(2) << std::setfill('0')
            << tm_t->tm_min << ":" << std::setw(2) << std::setfill('0')
            << tm_t->tm_sec << "] \033[0m " << str << std::endl;
}
void msg::warn(const std::string &str) {
  time_t now = time(nullptr);
  tm *tm_t = localtime(&now);
  std::cout << "\033[33m [" << std::setw(2) << std::setfill('0')
            << tm_t->tm_hour << ":" << std::setw(2) << std::setfill('0')
            << tm_t->tm_min << ":" << std::setw(2) << std::setfill('0')
            << tm_t->tm_sec << "] \033[0m " << str << std::endl;
}
void msg::err(const std::string &str) {
  time_t now = time(nullptr);
  tm *tm_t = localtime(&now);
  std::cout << "\033[31m [" << std::setw(2) << std::setfill('0')
            << tm_t->tm_hour << ":" << std::setw(2) << std::setfill('0')
            << tm_t->tm_min << ":" << std::setw(2) << std::setfill('0')
            << tm_t->tm_sec << "] \033[0m " << str << std::endl;
}
