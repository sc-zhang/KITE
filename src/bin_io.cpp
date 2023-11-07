//
// Created by zsc on 2023/11/7.
//

#include "bin_io.h"
#include <utility>

bin_io::bin_io(std::string file_name) {
  this->file_name = std::move(file_name);
}
bool bin_io::write(std::unordered_map<uint64_t, uint32_t> &mp_kmer,
                   std::unordered_map<uint32_t, std::string> &sample_id,
                   uint8_t k_size) {
  fs.open(this->file_name, std::ios_base::out | std::ios_base::binary);
  if (fs) {
    uint32_t sample_cnt = sample_id.size();
    Header header = Header();
    header.k_size = k_size;
    header.sample_count = sample_cnt + 1;
    header.record_count = mp_kmer.size();
    fs.write((char *)&header, sizeof(header));

    std::vector<std::string> samples(header.sample_count);
    samples[0] = "Unknown";
    for (auto &it : sample_id) {
      samples[it.first] = it.second;
    }
    for (auto &sample : samples) {
      uint16_t id_length = sample.size();
      fs.write((char *)&id_length, sizeof(id_length));
      fs.write(sample.c_str(), id_length);
    }
    for (auto &it : mp_kmer) {
      Record record = Record();
      record.kbin = it.first;
      record.sample_idx = it.second;
      fs.write((char *)&record, sizeof(record));
    }
    fs.close();
    return true;
  } else {
    return false;
  }
}
bool bin_io::read(uint8_t k_size) {
  fs.open(this->file_name, std::ios_base::in | std::ios_base::binary);
  if (fs) {
    Header header;
    fs.read((char *)&header, sizeof(header));
    std::vector<std::string> samples;
    for (uint32_t i = 0; i < header.sample_count; ++i) {
      uint16_t id_length;
      fs.read((char *)&id_length, sizeof(id_length));
      std::string sample;
      fs.read((char *)&sample, id_length);
      this->mp_sample_ids[i] = sample;
    }
    for (uint64_t i = 0; i < header.record_count; ++i) {
      Record record{};
      fs.read((char *)&record, sizeof(record));
      this->mp_kmer_records[record.kbin] = record.sample_idx;
    }
    fs.close();
    return true;
  } else {
    return false;
  }
}
