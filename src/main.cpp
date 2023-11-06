#include "fasta_io.h"
#include "k_bin.h"
#include <bitset>
#include <iostream>
#include <sstream>
#include <unordered_map>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "KITE <fasta_file> <k_size>" << std::endl;
  } else {
    std::string fasta_file;
    std::stringstream ss;
    int k_size;
    std::unordered_map<std::string, std::string> mp_seq;
    std::unordered_map<uint64_t, int> mp_kmer;
    std::unordered_map<std::string, int> id_sample;
    std::unordered_map<int, std::string> sample_id;

    fasta_file = argv[1];
    ss << argv[2];
    ss >> k_size;
    fasta_io ff = fasta_io(fasta_file);
    mp_seq = ff.read();

    // set sample index, 1-based
    int idx = 1;
    for (auto &it : mp_seq) {
      id_sample[it.first] = idx;
      sample_id[idx] = it.first;
      ++idx;
    }

    // get uniq kmer map
    // k_bin=>sample_index
    // value 0 means not unique
    for (auto &it : mp_seq) {
      k_bin kb = k_bin(it.second, k_size);
      while (kb.get_pos() <= it.second.size() - k_size) {
        kb.get_kmer();
        uint64_t kbin = kb.get_kbin();
        uint64_t rbin = kb.get_rbin();
        if (!mp_kmer.count(kbin)) {
          mp_kmer[kbin] = id_sample[it.first];
        } else {
          mp_kmer[kbin] = 0;
        }
        if (!mp_kmer.count(rbin)) {
          mp_kmer[rbin] = id_sample[it.first];
        } else {
          mp_kmer[rbin] = 0;
        }
      }
    }

    k_bin kb = k_bin("", k_size);
    // display kmer map
    for (auto &it : mp_kmer) {
      if (it.second == 0) {
        continue;
      }
      std::cout << kb.bin2kmer(it.first) << " " << sample_id[it.second]
                << std::endl;
    }
  }
  return 0;
}
