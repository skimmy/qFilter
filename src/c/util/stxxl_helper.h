#ifndef _STXXL_HELPER_H_
#define _STXXL_HELPER_H_

#include <stxxl/sorter>

#include "../read_sorter.h"

#define DEFAULT_BLOCK_SIZE 4096

typedef stxxl::sorter<read_record_t, ReadRecordComparator, DEFAULT_BLOCK_SIZE> read_record_sorter;

#endif
