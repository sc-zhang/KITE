//
// Created by zsc on 2023/11/6.
//

#ifndef KITE_MSG_H
#define KITE_MSG_H
#include <ctime>
#include <iostream>
#include <string>

class msg {
public:
  static void info(const std::string &str);
  static void warn(const std::string &str);
  static void err(const std::string &str);
};

#endif // KITE_MSG_H
