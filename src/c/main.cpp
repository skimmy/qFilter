#include <stdio.h>

#include <iostream>
#include <fstream>

#include "fasta_reader.hpp"
#include "read_sorter.hpp"

#include "util/seq.hpp"

string example = "@ecoli_sample:0 pos=510030 NoErr=GACAATTGCCTGCCAGCGGA Pe=0.115553";
string error_example = "@eco";
string fake_example="@b_a:12 pos=11 NoErr=GAA Pe=0.11";

int main(int argc, char** argv)
{
  printf("%d", PADDING_LENGTH);
  Debug::message("AA", "hi!!");
 
  // regex parsing
  read_header header_regex;  
  string_to_header_regex(example.c_str(), &header_regex);

  // is sequence framework from old libbio working???
  FastqRead r;
  std::ifstream ifs(argv[1]);
  while(!ifs.eof()) {
    ifs >> r;
    std::cout << r.getBases() << std::endl;
  }
  return 0;
}
