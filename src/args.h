//
// Created by zsc on 24-11-14.
//

#ifndef RUNE_ARGS_H
#define RUNE_ARGS_H

#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

class args {
public:
  std::string operate;
  std::string input_file;
  uint8_t k_size = 25;
  std::string output_file;
  bool args_enough = true;
  args(int argc, char *argv[]);
};

#endif // RUNE_ARGS_H
