#include <stdlib.h>
#include <getopt.h>

#include <iostream>

#include "options.hpp"

QFilterOptions opts;

void printUsage(std::ostream& os, const char* name, int exitCode) {
  os << "Usage:\n\t" << name << " [OPTIONS] fastq_file\n";
  exit(exitCode);
}

const char* shortOptions = "hX";
const struct option longOptions[] =
  {
    {"help", 0, NULL, 'h'},
    {"use-stdxxl", 0, NULL, 'X'}
  };

QFilterOptions::QFilterOptions() {
  this->SetDefaultValues();
}

QFilterOptions::QFilterOptions(int argn, char** argv) {
  this->SetDefaultValues();
  this->ParseCommandLineArguments(argn, argv);
}

QFilterOptions::~QFilterOptions() {
}

std::istream& operator>>(std::istream& is, QFilterOptions& opts) {
  return is;
}
std::ostream& operator<<(std::ostream& os, QFilterOptions& otps) {
  return os;
}

void QFilterOptions::ParseCommandLineArguments(int argn, char** argv) {
  int nextOption = -2;
  do {
    nextOption = getopt_long( argn, argv, shortOptions, longOptions, NULL);
    switch(nextOption) {
    case 'h':
      // print help and exit
      printUsage(std::cout, argv[0], 0);
      break;
    case 'X':
      this->stxxl = true;
      break;
    default:
      break;
    }
  } while(nextOption != -1);

  // decide whether to maintain this solution or impose
  // an option also for the input file(s)
  if (optind >= argn)  {
    printUsage(std::cout, argv[0], 1);
  } else {
    this->fastqFilePath = std::string(argv[optind]);
  }
}

void QFilterOptions::SetDefaultValues() {
  this->stxxl = false;
  this->fastqFilePath = ""; // is this redundant?
}
