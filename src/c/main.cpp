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
  
  __out_enabled = 0;

  // sorting
  string inFile = argv[1];
  string outFile = string(argv[1]) + ".out";
  sortFastq(inFile, outFile);

  return 0;
}
