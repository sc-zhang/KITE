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

void k_bin::get_kmer() {
  if(pos+k_size<=seq.size()){
    if(pos == 0){
      this->kbin = kmer2bin(seq.substr(pos, k_size));
      this->rbin = rev_bin(this->kbin);
    }else{
      this->kbin <<= 2;
      this->kbin |= mp_base[seq[pos+k_size-1]];
      this->kbin &= (1LL<<(k_size*2))-1;
      this->rbin >>= 2;
      this->rbin |= (~mp_base[seq[pos+k_size-1]])<<(k_size*2-2);
      this->rbin &= (1LL<<(k_size*2))-1;
    }
    this->pos++;
  }
}

uint64_t k_bin::get_kbin() { return this->kbin; }

uint64_t k_bin::get_rbin() { return this->rbin; }

uint64_t k_bin::get_pos() { return this->pos; }

void k_bin::reset_pos() { this->pos = 0; }
