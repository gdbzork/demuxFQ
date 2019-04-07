#include "index.h"
#include "indexDual.h"

bool IndexDual::matches(const Index &other) {
  return false;
}

unsigned short IndexDual::hammingDistance(Index const &other) {
  return 0;
}

size_t IndexDual::length(void) {
  return tag1.length() + tag2.length();
}

std::string const &IndexDual::repr(void) {
  tag = tag1 + "+" + tag2;
  return tag;
}
