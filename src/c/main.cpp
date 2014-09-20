#include <stdio.h>

#include <iostream>
#include <fstream>

#include "fasta_reader.hpp"
#include "read_sorter.hpp"

#include "util/options.hpp"
#include "util/seq.hpp"
#include "util/stxxl_helper.hpp"

string example = "@ecoli_sample:0 pos=510030 NoErr=GACAATTGCCTGCCAGCGGA Pe=0.115553";

int main(int argc, char** argv)
{
  // qFilter options
  QFilterOptions opts(argc,argv);
  
  __out_enabled = 0;
  
  // regex parsing
  read_header header_regex;  
  string_to_header_regex(example.c_str(), &header_regex);

  FastqRead r;
  std::ifstream ifs(argv[1]);
  string outFile = string(argv[1]) + ".out";
  std::ofstream ofs(outFile);
  sortFastqReadStxxl(ifs, ofs);
  //  std::ofstream ofs((string(argv[1]) + ))
  
  // int i = 10;
  // while(!ifs.eof() && i > 0) {
  //   ifs >> r;
  //   ReadRecordWrapper rrw(r);    
  //   //    std::cout << r.getQualities() << std::endl;
  //   std::cout << rrw.getRecord()->id << std::endl
  // 	      << rrw.getRecord()->sequence << std::endl
  // 	      << rrw.getRecord()->qualities << std::endl
  // 	      << rrw.getRecord()->error_probability << std::endl
  // 	      << std::endl;
  //   std::cout.flush();
  //   i--;
  // } 
  return 0;
}
