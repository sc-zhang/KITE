//
// Created by zsc on 2023/11/7.
//

#ifndef KITE_BIN_IO_H
#define KITE_BIN_IO_H
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

class Header {
public:
  std::string magic = "KITE";
  std::vector<std::string> samples;
};
class Record {
public:
  uint64_t kbin;
  int sample_idx;
};
class bin_io {
private:
  std::string file_name;
  std::fstream fs;

public:
  bin_io(std::string file_name);
  bool write(std::unordered_map<uint64_t, int> &mp_kmer,
             std::unordered_map<int, std::string> &sample_id);
};

#endif // KITE_BIN_IO_H
