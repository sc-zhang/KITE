//
// Created by zsc on 2023/11/7.
//

#include "bin_io.h"
#include "kite.h"
#include <cstring>
#include <utility>

bin_io::bin_io(std::string file_name) {
  this->file_name = std::move(file_name);
}

bin_io::bin_io(std::string file_name, uint8_t k_size) {
  this->file_name = std::move(file_name);
  this->k_size = k_size;
}

bool bin_io::write(std::unordered_map<uint64_t, uint32_t> &mp_kmer,
                   std::unordered_map<uint32_t, std::string> &sample_id) {
  fs.open(this->file_name, std::ios_base::out | std::ios_base::binary);
  if (fs) {
    Header header = Header();
    header.k_size = this->k_size;
    header.sample_count = sample_id.size();
    header.record_count = mp_kmer.size();
    fs.write((char *)&header, sizeof(header));

    std::vector<std::string> samples(header.sample_count);
    for (auto &it : sample_id) {
      samples[it.first - 1] = it.second;
    }
    for (auto &sample : samples) {
      uint16_t id_length = sample.size();
      fs.write((char *)&id_length, sizeof(id_length));
      fs.write(sample.c_str(), id_length);
    }
    for (auto &it : mp_kmer) {
      Record record = Record();
      record.kbin = it.first;
      if (it.second == kite::flag::unknown) {
        continue;
      }
      record.sample_idx = it.second;
      fs.write((char *)&record, sizeof(record));
    }
    fs.close();
    return true;
  } else {
    return false;
  }
}

bool bin_io::read() {
  fs.open(this->file_name, std::ios_base::in | std::ios_base::binary);
  if (fs) {
    Header header;
    fs.read((char *)&header, sizeof(header));
    if (strcmp(header.magic, "KITE") != 0) {
      fs.close();
      return false;
    }
    this->k_size = header.k_size;
    for (uint32_t i = 0; i < header.sample_count; ++i) {
      uint16_t id_length;
      fs.read((char *)&id_length, sizeof(id_length));
      std::string sample;
      char *buffer = new char[id_length + 1];
      fs.read(buffer, id_length);
      buffer[id_length] = '\0';
      sample = buffer;
      this->id_name[i + 1] = sample;
      this->sample_id[sample] = i + 1;
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
