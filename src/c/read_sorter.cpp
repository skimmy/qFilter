#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <cmath>
#include <vector>
#include <algorithm>

#include "read_sorter.hpp"
#include "util/options.hpp"
#include "util/common.hpp"



read_record_t read_record_min; 
read_record_t read_record_max; 

ReadRecordWrapper::ReadRecordWrapper() {
  this->read = new read_record_t;
  // all characters vector are initalized with zeros
  memset(this->read->sequence, 0, MAX_READ_LENGTH);
  memset(this->read->qualities, 0, MAX_READ_LENGTH);
  memset(this->read->name, 0, MAX_NAME_LENGTH);
  memset(this->read->original, 0, MAX_READ_LENGTH);
  // and size is set to 0
  this->read->actual_read_length = 0;
}

ReadRecordWrapper::~ReadRecordWrapper() {
  delete this->read;
  this->read = NULL;
}

ReadRecordWrapper::ReadRecordWrapper(char* read_seq, char* read_quals, read_header* header) 
  : ReadRecordWrapper()
{
  this->read->actual_read_length = min((int)strlen(read_seq), MAX_READ_LENGTH);
  strncpy(this->read->sequence, read_seq, this->read->actual_read_length);
  strncpy(this->read->qualities, read_quals, this->read->actual_read_length);
  HeaderToRecord(header, this->read); 
}

ReadRecordWrapper::ReadRecordWrapper(const FastqRead& read, bool customHdr) 
  : ReadRecordWrapper()
{
  this->read->actual_read_length = min((int) read.length(), MAX_READ_LENGTH);
  strncpy(this->read->sequence, read.getBases().c_str(), this->read->actual_read_length);
  strncpy(this->read->qualities, read.getQualities().c_str(), this->read->actual_read_length);
  read_header* header = default_header_init();
  // custom header already contains read's error probability
  if (customHdr) {
    int matchCode = string_to_header_regex(read.getHeader().c_str(), header)             ;    
    if (matchCode == NO_ERR) {
      this->HeaderToRecord(header, this->read);
    }
  }
  // in this case probability must be computed from scratch
  else {
    const char * hdr = read.getHeader().c_str();
    strncpy(this->read->name, hdr+1, strlen(hdr));
    computeProbability(this->read);
  }
  header_free(header);  
}

ReadRecordWrapper::ReadRecordWrapper(const read_record_t& record)
{
  this->read = new read_record_t;
  memcpy(this->read, &record, sizeof(read_record_t));
}

// WARNING: this method does not check the validity of the fields in the
// heder pointer, nor does it check if such pointer is valid (be aware).
void ReadRecordWrapper::HeaderToRecord(read_header* header, read_record_t* record) {
  record->id = (uint64_t) atoi(header->id);
  record->sequencing_position = (int64_t) header->sequencing_position;
  record->error_probability = header->error_probability;
  size_t tmp = 0;
  if (header->name != NULL) {
    tmp = min(MAX_NAME_LENGTH, (int)strlen(header->name));
    strncpy(record->name, header->name, tmp);
  }

  if (header->original != NULL) {
    tmp = min(MAX_READ_LENGTH, (int)strlen(header->original));
    strncpy(record->original, header->original, tmp);
  }  
}

read_record_t* ReadRecordWrapper::getRecord() {
  return this->read;
}

read_record_t* ReadRecordWrapper::cloneRecord(read_record_t* dest) {
  memcpy(dest, this->read, sizeof(read_record_t));
  return dest;
}


std::ostream& operator<< (std::ostream& os, const ReadRecordWrapper& record) { 
  
  OutputFormat outForm = opts.getOutputFormat();
  bool useCustomHdr = opts.isCustomHeaderEnabled();
  char headChar = '>';
  if (outForm == Fastq) {
    headChar = '@';
  }
  char header[2048];
  if (useCustomHdr) {
    sprintf(header, "%c%s:%d pos=%d NoErr=%s Pe=%.15f", headChar, record.read->name, (int)record.read->id, 
	    (int)record.read->sequencing_position, record.read->original, record.read->error_probability);
  } else {
    sprintf(header, "%c%s", headChar, record.read->name);
  }
  os << header << std::endl;
  os << record.read->sequence << std::endl;
  if (outForm == Fastq) {
    os << "+" << std::endl << record.read->qualities << std::endl;
  }
return os;
}

void sortFastqInternal(std::ifstream& input, std::ofstream& sorted, double fraction, size_t readsCount = -1) {
  uint64_t M = (readsCount > 0) ? readsCount : MaxUint64;
  FastqRead r;  
  std::vector<read_record_t> v;
  size_t count = 0;
  while((!input.eof()) && (count < M)) {
    if ((count % 10000) == 0) {
      std::cout << count << std::endl;
      std::cout.flush();
    }
    input >> r;
    ReadRecordWrapper rrw(r);
    if (!(r.getSequenceLength() > 0)) {
      continue;
    }
    read_record_t rrt;
    rrw.cloneRecord(&rrt);
    v.push_back(rrt);
    ++count;
  } 
  
  std::cout << "Loaded " << count << " reads" << std::endl;
  std::cout << "Sorting (internal)..." << std::endl;
  std::cout.flush();
  std::sort(v.begin(), v.end(), ReadRecordComparator());
  size_t bar_n = fraction * v.size();

  for (uint64_t i = 0; i < bar_n; ++i) {
    ReadRecordWrapper rrw(v[i]);
    sorted << rrw;
  }
}
 
void sortFastq(const std::string& inFilePath, const std::string& outFilePath) {
  std::ifstream ifs(inFilePath);
  std::ofstream ofs(outFilePath);
  double fraction = opts.getFraction();
  size_t readsCount = opts.getReadsCount();
  if (opts.isStxxlEnabled()) {
    sortFastqReadStxxl(ifs, ofs, fraction, readsCount);
  } else {
    sortFastqInternal(ifs, ofs, fraction, readsCount);
  }
  ifs.close();
  ofs.close();
}

void computeProbability(read_record_t* r) {
  size_t n = r->actual_read_length;
  size_t offset = 33; // at the moment only PHRED+33 encoding is supported
  double p = 1.0;
  for (size_t i = 0; i < n; ++i) {
    int q = r->qualities[i] - offset;
    // IMPORTANT change with lookup table before release
    double pq = pow(10, (-1.0 * q / 10.0));
    p *= (1.0 - pq);
  }
  r->error_probability = p;
}
