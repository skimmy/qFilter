#include <stdlib.h>
#include <getopt.h>

#include <iostream>

#include "options.hpp"

QFilterOptions opts;

void printUsage(std::ostream& os, const char* name, int exitCode) {
  os << "Usage:\n\t" << name << " [OPTIONS] fastq_file\n";
  exit(exitCode);
}

const char* shortOptions = "hXf:";
const struct option longOptions[] =
  {
    {"help", 0, NULL, 'h'},
    {"use-stdxxl", 0, NULL, 'X'},
    {"fraction", 1, NULL, 'f'}
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
  os << "Fastq Input File: " << opts.fastqFilePath << std::endl;
  os << "Use stxxl library " << opts.stxxl << std::endl;
  os << "Input fraction    " << opts.fraction << std::endl;
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
    case 'f':
      this->fraction = atof(optarg);
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
  this->fraction = 1.0;
  this->fastqFilePath = ""; // is this redundant?
}
