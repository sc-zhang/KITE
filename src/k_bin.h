//
// Created by zsc on 2023/11/2.
//

#ifndef KATE_K_BIN_H
#define KATE_K_BIN_H
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

class k_bin {
private:
  uint64_t k_size;
  uint64_t pos;
  uint64_t kbin;
  uint64_t rbin;
  uint64_t mask;
  std::string seq;
  std::unordered_map<char, u_int64_t> mp_base = {
      {'A', 0LL}, {'C', 1LL}, {'G', 2LL}, {'T', 3LL}};
  std::unordered_map<u_int64_t, char> mp_bin = {
      {0LL, 'A'}, {1LL, 'C'}, {2LL, 'G'}, {3LL, 'T'}};

public:
  explicit k_bin(std::string seq, uint64_t k_size = 17) {
    this->seq = std::move(seq);
    this->k_size = k_size;
    this->pos = 0;
    this->kbin = 0;
    this->rbin = 0;
    if (k_size < 32) {
      mask = (1LL << (k_size * 2)) - 1;
    } else {
      mask = 0xFFFFFFFFFFFFFFFF;
    }
  }
  uint64_t kmer2bin(const std::string &k_mer);
  std::string bin2kmer(uint64_t k_bin);
  uint64_t rev_bin(uint64_t k_bin) const;
  void get_kmer();
  uint64_t get_kbin() const;
  uint64_t get_rbin() const;
  uint64_t get_pos() const;
  void reset_pos();
};

#endif // KATE_K_BIN_H
