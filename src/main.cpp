#include "bin_io.h"
#include "fasta_io.h"
#include "k_bin.h"
#include "kite.h"
#include "msg.h"
#include <bitset>
#include <iostream>
#include <unordered_map>

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cout << "kite <fasta_file> <k_size> <kmer_file>" << std::endl;
  } else {
    std::string fasta_file;
    std::string kmer_file;
    std::string k_size_arg;
    uint8_t k_size = 0;
    std::unordered_map<std::string, std::string> mp_seq;
    std::unordered_map<uint64_t, uint32_t> mp_kmer;
    std::unordered_map<std::string, uint32_t> id_sample;
    std::unordered_map<uint32_t, std::string> sample_id;

    fasta_file = argv[1];
    k_size_arg = argv[2];
    for (char &c : k_size_arg) {
      k_size *= 10;
      k_size += c - '0';
    }
    kmer_file = argv[3];

    std::ifstream check_file(kmer_file);
    if (check_file.good()) {
      msg::info("Loading k-mer");
      bin_io bio = bin_io(kmer_file);
      k_bin kb = k_bin("", k_size);
      bio.read();
      for (auto &it : bio.mp_kmer_records) {
        if (it.second == 0) {
          continue;
        }
        std::cout << kb.bin2kmer(it.first) << " "
                  << bio.mp_sample_ids[it.second] << std::endl;
      }
    } else {
      msg::info("Loading fasta");
      fasta_io ff = fasta_io(fasta_file);
      mp_seq = ff.read();

      // set sample index, 1-based
      uint32_t idx = 1;
      for (auto &it : mp_seq) {
        id_sample[it.first] = idx;
        sample_id[idx] = it.first;
        ++idx;
      }

      // get uniq kmer map
      // k_bin=>sample_index
      // value 0 means not unique
      msg::info("Generating k-mers with " + std::to_string(k_size));
      for (auto &it : mp_seq) {
        k_bin kb = k_bin(it.second, k_size);
        while (kb.get_pos() <= it.second.size() - k_size) {
          kb.get_kmer();
          uint64_t kbin = kb.get_kbin();
          uint64_t rbin = kb.get_rbin();
          if (!mp_kmer.count(kbin)) {
            mp_kmer[kbin] = id_sample[it.first];
          } else {
            mp_kmer[kbin] = kite::unknown;
          }
          if (!mp_kmer.count(rbin)) {
            mp_kmer[rbin] = id_sample[it.first];
          } else {
            mp_kmer[rbin] = kite::unknown;
          }
        }
      }

      msg::info("Writing k-mers");
      bin_io bio = bin_io(kmer_file, k_size);
      bio.write(mp_kmer, sample_id);
      msg::info("Finished");
    }
  }
  return 0;
}
