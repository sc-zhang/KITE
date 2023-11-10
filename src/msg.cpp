//
// Created by zsc on 2023/11/6.
//

#include "msg.h"
#include <iomanip>

void msg::print(const std::string &str, const std::string &color_string) {
  time_t now = time(nullptr);
  tm *tm_t = localtime(&now);
  if (this->use_cout) {
    std::cout << color_string << std::setw(2) << std::setfill('0')
              << tm_t->tm_hour << ":" << std::setw(2) << std::setfill('0')
              << tm_t->tm_min << ":" << std::setw(2) << std::setfill('0')
              << tm_t->tm_sec << "] \033[0m " << str << std::endl;
  } else {
    std::cerr << color_string << std::setw(2) << std::setfill('0')
              << tm_t->tm_hour << ":" << std::setw(2) << std::setfill('0')
              << tm_t->tm_min << ":" << std::setw(2) << std::setfill('0')
              << tm_t->tm_sec << "] \033[0m " << str << std::endl;
  }
}
void msg::info(const std::string &str) { this->print(str, "\033[32m ["); }
void msg::warn(const std::string &str) { this->print(str, "\033[33m ["); }
void msg::err(const std::string &str) { this->print(str, "\031[32m ["); }
