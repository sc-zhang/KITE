//
// Created by zsc on 2023/11/7.
//

#include "bin_io.h"

#include <utility>
bin_io::bin_io(std::string file_name) {
  this->file_name = std::move(file_name);
}
bool bin_io::write(std::unordered_map<uint64_t, int> &mp_kmer,
                   std::unordered_map<int, std::string> &sample_id) {
  fs.open(this->file_name, std::ios_base::out | std::ios_base::binary);
  if (fs) {
    int sample_cnt = (int)sample_id.size();
    Header header = Header();
    header.samples.resize(sample_cnt + 1);
    header.sample_count = sample_cnt + 1;
    header.samples[0] = "Unknown";
    for (auto &it : sample_id) {
      header.samples[it.first] = it.second;
    }
    header.record_count = (int)mp_kmer.size();
    fs.write((char *)&header, sizeof(header));
    
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
