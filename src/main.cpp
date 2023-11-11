#include "bin_io.h"
#include "dumper.h"
#include "k_bin.h"
#include "kite.h"
#include "loader.h"
#include "msg.h"
#include <bitset>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cout << "kite <fasta_file> <k_size> <kmer_file>" << std::endl;
  } else {
    std::string fasta_file;
    std::string kmer_file;
    std::string k_size_arg;
    uint8_t k_size = 0;

    fasta_file = argv[1];
    k_size_arg = argv[2];
    for (char &c : k_size_arg) {
      k_size *= 10;
      k_size += c - '0';
    }
    kmer_file = argv[3];

    std::ifstream check_file(kmer_file);
    if (check_file.good()) {
      loader kmer_loader = loader(kmer_file, k_size);
      kmer_loader.load();
      k_bin kb = k_bin("", k_size);
      for (auto &it : kmer_loader.get_kmer_db()) {
        if (it.second == kite::flag::unknown) {
          continue;
        }
        std::cout << kb.bin2kmer(it.first) << " "
                  << kmer_loader.get_sample_name(it.second) << std::endl;
      }
    } else {
      dumper kmer_dumper = dumper(fasta_file, k_size, kmer_file);
      kmer_dumper.extract();
      kmer_dumper.save();
    }
    check_file.close();
  }
  return 0;
}
