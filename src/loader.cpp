//
// Created by zsc on 2023/11/11.
//

#include "loader.h"

void loader::load() {
  msg message = msg(false);
  message.info("Loading k-mer");
  k_bin kb = k_bin("", k_size);
  bio.read();
  message.info("Loaded");
}
std::unordered_map<uint64_t, uint32_t> loader::get_kmer_db() const {
  return this->bio.mp_kmer_records;
}
uint32_t loader::get_sample_id(const std::string &sample) {
  return this->bio.sample_id[sample];
};
std::string loader::get_sample_name(const uint32_t &id) {
  return this->bio.id_name[id];
}
