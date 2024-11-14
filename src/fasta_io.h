//
// Created by zsc on 2023/11/6.
//

#ifndef RUNE_FASTA_IO_H
#define RUNE_FASTA_IO_H
#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>

class fasta_io {
private:
  std::string file_name;

public:
  explicit fasta_io(std::string file_name) {
    this->file_name = std::move(file_name);
  }
  // read fasta file and return an unordered_name:
  // sequence_id => sequence
  std::unordered_map<std::string, std::string> read();
};

#endif // RUNE_FASTA_IO_H
