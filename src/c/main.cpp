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
  opts.ParseCommandLineArguments(argc,argv);
  std::cout << "--------- OPTIONS ---------" << std::endl;
  std::cout << opts;
  std::cout << "---------------------------" << std::endl;
  
  __out_enabled = 0;

  // sorting
  string inFile = opts.getFastqFilePath();
  string outFile = string(inFile + ".out");
  sortFastq(inFile, outFile);

  return 0;
}
