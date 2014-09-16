#include "read_sorter.h"

read_record_t read_record_min; 
read_record_t read_record_max; 

ReadRecordWrapper::ReadRecordWrapper() {
  this->read = new read_record_t;
}

ReadRecordWrapper::~ReadRecordWrapper() {
  delete this->read;
  this->read = NULL;
}

ReadRecordWrapper::ReadRecordWrapper(char* read_seq, char* read_quals, read_header* header)  : ReadRecordWrapper() {
}
