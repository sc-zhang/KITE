//
// Created by zsc on 2023/11/2.
//

#include "k_bin.h"

uint64_t k_bin::kmer2bin(const std::string &k_mer) {
  uint64_t bin = 0;
  for (char i : k_mer) {
    bin <<= 2;
    bin |= mp_base[i];
  }
  return bin;
}

std::string k_bin::bin2kmer(uint64_t k_bin) {
  std::string k_mer;
  for (int i = 0; i < k_size; i++) {
    k_mer += mp_bin[k_bin & 3];
    k_bin >>= 2;
  }
  reverse(k_mer.begin(), k_mer.end());
  return k_mer;
}

uint64_t k_bin::rev_bin(uint64_t k_bin) const {
  k_bin = (k_bin & 0xCCCCCCCCCCCCCCCC) >> 2 | (k_bin & 0x3333333333333333) << 2;
  k_bin = (k_bin & 0xF0F0F0F0F0F0F0F0) >> 4 | (k_bin & 0x0F0F0F0F0F0F0F0F) << 4;
  k_bin = (k_bin & 0xFF00FF00FF00FF00) >> 8 | (k_bin & 0x00FF00FF00FF00FF) << 8;
  k_bin = (k_bin & 0xFFFF0000FFFF0000) >> 16 | (k_bin & 0x0000FFFF0000FFFF) << 16;
  k_bin = k_bin >> 32 | k_bin << 32;
  k_bin >>= 64 - k_size * 2;
  return (~k_bin) & ((1LL << (k_size * 2)) - 1);
}

std::unordered_set<uint64_t> k_bin::get_kmers(const std::string& seq) {
  std::unordered_set<uint64_t>k_bins;
  uint64_t k_bin = 0, r_bin = 0;
  for(int i=0; i+k_size<=seq.size(); ++i){
    if(i==0){
      k_bin = kmer2bin(seq.substr(i, k_size));
      r_bin = rev_bin(k_bin);
    }else{
      k_bin <<= 2;
      k_bin |= mp_base[seq[i+k_size-1]];
      k_bin &= (1LL<<(k_size*2))-1;
      r_bin >>= 2;
      r_bin |= (~mp_base[seq[i+k_size-1]])<<(k_size*2-2);
      r_bin &= (1LL<<(k_size*2))-1;
    }
    k_bins.insert(k_bin);
    k_bins.insert(r_bin);
  }
  return k_bins;
}
