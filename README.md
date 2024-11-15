# RUNE: A Tool for Extracting Unique K-mers with Single Fasta File

## Introduction

RUNE (Retrieve UNique k-mErs) is a simple tool for extracting unique k-mers of multiple sequences in one fasta file.

## Installation

```bash
git clone https://github.com/sc-zhang/RUNE
cd RUNE
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=release -DCMAKE_INSTALL_PREFIX=/path/to/install ..
make install
```

## Usage

```bash
usage: rune [-h] {dump,load} -i input_file -k kmer_size -o output_file
options:
  -h, --help        show this help message and exit
  -i input_file     Input file
  -k kmer_size      kmer size, should be [3, 32], default=25
  -o output_file    Output file
```

1. dump is used for getting unique k-mers with "kmer_size" of each sequences in "input_file", and write into a binary
   file "output_file".

> Example:
> ```bash
> rune dump -i ref.fasta -k 17 -o ref.kbin
> ```

2. load is used for reading k-mer sequences and samples in dumped binary file, and write into a text file.

> Example
> ```bash
> rune load -i ref.kbin -k 17 -o ref.kmers
> ```
> kmers file is a text file like below
> ```text
> AATGCATAGAGCAG seq1  
> AATGCATTAGAGAG seq2
> ```

**Notice**
> 1. id of sequence would be cut at first space/tab
> 2. Only "ATGCN" should be contained in sequence
> 3. k-mer contain "N" would be dropped
