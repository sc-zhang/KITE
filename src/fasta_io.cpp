//
// Created by zsc on 2023/11/6.
//

#include "fasta_io.h"

std::unordered_map<std::string, std::string> fasta_io::read() {
  std::unordered_map<std::string, std::string> mp_seq;
  std::ifstream fs;
  std::string line;
  fs.open(this->file_name);
  if (fs) {
    std::string seq_id;
    std::string seq;
    while (std::getline(fs, line)) {
      if (line[0] == '>') {
        if (!seq.empty()) {
          seq.erase(std::remove_if(seq.begin(), seq.end(), ::isspace),
                    seq.end());
          transform(seq.begin(), seq.end(), seq.begin(), ::toupper);
          mp_seq[seq_id] = seq;
        }
        int space_pos = 0;
        for(int i=0; i<line.size(); ++i){
          if(line[i] == ' ' || line[i] == '\t'){
            space_pos = i;
            break;
          }
        }
        seq_id = line.substr(1, space_pos - 1);
        seq_id.erase(std::remove_if(seq_id.begin(), seq_id.end(), ::isspace),
                     seq_id.end());
        seq.clear();
      } else {
        seq += line;
      }
    }
    seq.erase(std::remove_if(seq.begin(), seq.end(), ::isspace), seq.end());
    transform(seq.begin(), seq.end(), seq.begin(), ::toupper);
    mp_seq[seq_id] = seq;
    seq_id.clear();
    seq.clear();
    fs.close();
    return mp_seq;
  } else {
    return {};
  }
}