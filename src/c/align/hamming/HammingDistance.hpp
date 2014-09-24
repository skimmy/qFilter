#ifndef _HAMMING_DISTANCE_H_
#define _HAMMING_DISTANCE_H_

#include <string>

#define DEFAULT_MASK_SIZE 256

/**
 * \brief class representing a mask correspondinf to a Hamming Distance, one for
 * match and zero for mismatch
 */
class HammingDistanceMask {
private:
  std::string* mask;

public:
  HammingDistanceMask();
  ~HammingDistanceMask();
};

#endif
