#include <stdio.h>

#ifdef MTRACE
#include <mcheck.h>
#endif

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
  #ifdef MTRACE
  std::cout << "[MTRACE] - Enabled" << std::endl;
  mtrace();
  #endif  
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


  /*read_header* header = new read_header;
  string_to_read_header(example.c_str(), header);
  std::cout << "--------------------------------------" << std::endl;
  std::cout << "Name:        " << header->name << std::endl;
  std::cout << "Id:          " << header->id << std::endl;
  std::cout << "Pos:         " << header->sequencing_position << std::endl;
  std::cout << "NoErr:       " << header->original << std::endl;
  std::cout << "Pe:          " << header->error_probability << std::endl;
  std::cout << "--------------------------------------" << std::endl;
  std::cout.flush();
  header_free(header);  
  delete header;*/
  
  #ifdef MTRACE
  muntrace();
  #endif
  return 0;
}
