#include "stxxl_helper.hpp"

typedef stxxl::sorter<read_record_t, ReadRecordComparator, DEFAULT_BLOCK_SIZE> read_record_sorter;

void sortFastqReadStxxl(std::ifstream & input, std::ofstream& sorted) {
  FastqRead r;
  
  read_record_sorter sorter(ReadRecordComparator(), DEFAULT_MEM_SIZE);
  
  while(!input.eof()) {
    input >> r;
    ReadRecordWrapper rrw(r);
    read_record_t rrt = rrw.cloneRecord();
    //    std::cout << rrt.sequence << std::endl;
    sorter.push(rrt);
  }
  sorter.sort();
  while(!sorter.empty()) {
    ReadRecordWrapper rrw(*sorter);
    sorted << rrw;
    ++sorter;
  } 
}

