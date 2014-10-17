#include "stxxl_helper.hpp"

typedef stxxl::sorter<read_record_t, ReadRecordComparator, DEFAULT_BLOCK_SIZE> read_record_sorter;

void sortFastqReadStxxl(std::ifstream & input, std::ofstream& sorted, double fraction) {
  FastqRead r;
  
  read_record_sorter sorter(ReadRecordComparator(), DEFAULT_MEM_SIZE);
  size_t count = 0;
  
  while(!input.eof()) {
    if ((count % 10000) == 0) {
      std::cout << count << std::endl;
      std::cout.flush();
    }
    input >> r;
    ReadRecordWrapper rrw(r);
    read_record_t rrt;
    rrw.cloneRecord(&rrt);
    sorter.push(rrt);
    ++count;
  }
  std::cout << "Loaded " << count << " reads" << std::endl;
  std::cout << "Sorting (stxxl)..." << std::endl;
  std::cout.flush();
  sorter.sort();
  size_t bar_n = count * fraction;
  size_t i = 0;
  while(!sorter.empty() && (i < bar_n)) {
    ReadRecordWrapper rrw(*sorter);
    sorted << rrw;
    ++sorter;
    ++i;
  } 
}

