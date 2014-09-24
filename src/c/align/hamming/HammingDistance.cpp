#include "HammingDistance.hpp"

#include <stdlib.h>

// TODO: this function will, eventually, be moved to a strutil.hpp or similar to
//       indicated that it is an actual usefull function that can be used in any
//       other contest
/**
 * \brief fills str with n occurances of the character c
 */
void fillStringWithChars(std::string &str, char c, size_t n) {
  str.clear();
  for (size_t i = 0; i < n; ++i) {
    str += c;
  }
}

HammingDistanceMask::HammingDistanceMask() {
  this->mask = new std::string();
}

HammingDistanceMask::~HammingDistanceMask() {
  if (this->mask != NULL) {
    delete this->mask;
  }
}
