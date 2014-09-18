#include <string.h>
#include <stdlib.h>

#include <algorithm>

#include "read_sorter.hpp"

#include "util/seq.hpp"

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

ReadRecordWrapper::ReadRecordWrapper(const FastqRead& read) 
  : ReadRecordWrapper()
{
  this->read->actual_read_length = min((int) read.length(), MAX_READ_LENGTH);
  strncpy(this->read->sequence, read.getBases().c_str(), this->read->actual_read_length);
  strncpy(this->read->qualities, read.getQualities().c_str(), this->read->actual_read_length);
  read_header header;
  string_to_header_regex(read.getHeader().c_str(), &header);
  this->HeaderToRecord(&header, this->read);
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


std::ostream& operator<< (std::ostream& os, const ReadRecordWrapper& record) {
  return os;
}

