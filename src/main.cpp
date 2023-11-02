#include "k_bin.h"
#include <bitset>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "KATE <seq> <k_size>" << std::endl;
  }else{
    std::string seq = argv[1];
    std::stringstream ss;
    ss << argv[2];
    int k_size;
    ss >> k_size;
    k_bin kb = k_bin(k_size);
    std::unordered_set<uint64_t> kbins = kb.get_kmers(seq);
    for(const uint64_t& bin: kbins){
      std::cout<<kb.bin2kmer(bin)<<std::endl;
    }
  }
  return 0;
}
