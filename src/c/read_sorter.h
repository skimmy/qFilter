#ifndef _READ_SORTER_H_
#define _READ_SORTER_H_

#include "fasta_reader.h"

#include <float.h>
#include <cstdint>

#define WORD_SIZE         8
#define MAX_NAME_LENGTH   512
#define MAX_READ_LENGTH   1024
#define PADDING_LENGTH    (2048 - 4 * WORD_SIZE - MAX_NAME_LENGTH - MAX_READ_LENGTH)

/*
 * This structure contains the full read record which is composed by:
 *    - One sequence of characters for the bases
 *    - One sequence of characters for the quality
 *    - The header
 *       - id of the read
 *       - error probability of the read
 *       - name of the read
 *       - a character sequence used to describe the original source
 *       - a padding part used for summing to 4096 bytes for the size
 */ 

typedef struct {
  uint64_t id;
  int64_t sequencing_position;
  double error_probability;

  uint64_t actual_read_length;

  char sequence[MAX_READ_LENGTH];
  char qualities[MAX_READ_LENGTH];

  char name[MAX_NAME_LENGTH];
  char original[MAX_READ_LENGTH];
} read_record_t;

extern read_record_t read_record_min;
extern read_record_t read_record_max;

/**
 * This is the comparator for the read_record_t struct that is used to run
 * external sorter from stxxl library. Although it has been developed with the
 * goal of fullfilling stxxl specifications, it can be used elsewhere.
 */
class ReadRecordComparator {
 public:
  bool operator()(const read_record_t &a, const read_record_t &b) const {
    return (a.error_probability < b.error_probability);
  }
  read_record_t min_value() const {
    read_record_min.error_probability = DBL_MIN;
    return read_record_min;
  }

  read_record_t max_value() const {
    read_record_max.error_probability = DBL_MAX;
     return read_record_max;
    
  }
};

/**
 * This class is used for convenience and it is basically a wrapper class for
 * the read_record_t containing all basic utilities like: initializers,
 * conversion methods, ...
 */

class ReadRecordWrapper {
 private:
  read_record_t* read;
 public:
  /**
   * \brief Default constructor
   */
  ReadRecordWrapper();
  ReadRecordWrapper(char* read_seq, char* read_quals, read_header* header);
  ~ReadRecordWrapper();

 private:
  void HeaderToRecord(read_header* header, read_record_t* record);
  
};

#endif
