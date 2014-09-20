#ifndef _STXXL_HELPER_H_
#define _STXXL_HELPER_H_

#include <iostream>
#include <fstream>

#include <stxxl/sorter>

#include "seq.hpp"
#include "../read_sorter.hpp"

#define DEFAULT_BLOCK_SIZE 4096
#define DEFAULT_MEM_SIZE   (1024 * 1024 * 64)

typedef stxxl::sorter<read_record_t, ReadRecordComparator, DEFAULT_BLOCK_SIZE> read_record_sorter;

/**
 * \brief sort fastq file using stxxl external sorting
 */
void sortFastqReadStxxl(std::ifstream & input, std::ofstream& sorted) {
  FastqRead r;
  
  read_record_sorter sorter(ReadRecordComparator(), DEFAULT_MEM_SIZE);
  
  while(!input.eof()) {
    input >> r;
    ReadRecordWrapper(r);
    sorter.push(r.cloneRecord());
  }
  sorter.sort();
  // while(!sorter.empy()) {

  // } 
}

#endif
