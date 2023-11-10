//
// Created by zsc on 2023/11/6.
//

#ifndef KITE_MSG_H
#define KITE_MSG_H
#include <ctime>
#include <iostream>
#include <string>

class msg {
private:
  void print(const std::string &str, const std::string &color_string);
  bool use_cout;

public:
  explicit msg(bool use_cout) { this->use_cout = use_cout; }
  void info(const std::string &str);
  void warn(const std::string &str);
  void err(const std::string &str);
};

#endif // KITE_MSG_H
