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
  char magic[4] = {'K', 'I', 'T', 'E'};
  uint8_t k_size;
  uint32_t sample_count;
  uint64_t record_count;
};

class Record {
public:
  uint64_t kbin;
  uint32_t sample_idx;
};

class bin_io {
private:
  std::string file_name;
  std::fstream fs;

public:
  std::unordered_map<uint64_t, uint32_t> mp_kmer_records;
  std::unordered_map<uint32_t, std::string> mp_sample_ids;
  explicit bin_io(std::string file_name);
  bool write(std::unordered_map<uint64_t, uint32_t> &mp_kmer,
             std::unordered_map<uint32_t, std::string> &sample_id,
             uint8_t k_size);
  bool read(uint8_t k_size);
};

#endif // KITE_BIN_IO_H
