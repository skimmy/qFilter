#ifndef _STXXL_HELPER_H_
#define _STXXL_HELPER_H_

#include <iostream>
#include <fstream>

#include <stxxl/sorter>

#include "seq.hpp"
#include "../read_sorter.hpp"

#define DEFAULT_BLOCK_SIZE 32 * 4096
#define DEFAULT_MEM_SIZE   (1024 * 1024 * 64)

/**
 * \brief sort fastq file using stxxl external sorting
 */
void sortFastqReadStxxl(std::ifstream & input, std::ofstream& sorted);

#endif
