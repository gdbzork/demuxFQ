#include "index.h"
#include "indexSingle.h"

bool IndexSingle::matches(const Index &other) {
  return false;
}

unsigned short IndexSingle::hammingDistance(Index const &other) {
  return 0;
}

size_t IndexSingle::length(void) {
  return tag.length();
}

std::string const &IndexSingle::repr(void) {
  return tag;
}
