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
  std::unordered_map<char, u_int64_t> mp_base = {
      {'A', 0LL}, {'C', 1LL}, {'G', 2LL}, {'T', 3LL}};
  std::unordered_map<u_int64_t, char> mp_bin = {
      {0LL, 'A'}, {1LL, 'C'}, {2LL, 'G'}, {3LL, 'T'}};

public:
  k_bin() { this->k_size = 17; }
  explicit k_bin(uint64_t k_size) { this->k_size = k_size; }
  uint64_t kmer2bin(const std::string &k_mer);
  std::string bin2kmer(uint64_t k_bin);
  uint64_t rev_bin(uint64_t k_bin) const;
  std::unordered_set<uint64_t> get_kmers(const std::string& seq);
};

#endif // KATE_K_BIN_H
