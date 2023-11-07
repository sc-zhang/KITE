#include "bin_io.h"
#include "fasta_io.h"
#include "k_bin.h"
#include "msg.h"
#include <bitset>
#include <iostream>
#include <sstream>
#include <unordered_map>

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cout << "KITE <fasta_file> <k_size> <kmer_file>" << std::endl;
  } else {
    std::string fasta_file;
    std::string kmer_file;
    std::stringstream ss;
    msg msg;
    int k_size;
    std::unordered_map<std::string, std::string> mp_seq;
    std::unordered_map<uint64_t, int> mp_kmer;
    std::unordered_map<std::string, int> id_sample;
    std::unordered_map<int, std::string> sample_id;

    fasta_file = argv[1];
    ss << argv[2];
    ss >> k_size;
    kmer_file = argv[3];

    msg::info("Loading fasta");
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
    msg::info("Generating k-mers");
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

    msg::info("Writing k-mers");
    bin_io bio = bin_io(kmer_file);
    bio.write(mp_kmer, sample_id);
    msg::info("Finished");
  }
  return 0;
}
