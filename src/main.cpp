#include "k_bin.h"
#include <bitset>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "KITE <seq> <k_size>" << std::endl;
  } else {
    std::string seq = argv[1];
    std::stringstream ss;
    ss << argv[2];
    int k_size;
    ss >> k_size;
    k_bin kb = k_bin(seq, k_size);
    while (kb.get_pos() <= seq.size() - k_size) {
      kb.get_kmer();
      std::cout << kb.bin2kmer(kb.get_kbin()) << std::endl;
      std::cout << kb.bin2kmer(kb.get_rbin()) << std::endl;
    }
    kb.reset_pos();
  }
  return 0;
}
