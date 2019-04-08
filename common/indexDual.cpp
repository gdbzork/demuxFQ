#include "index.h"
#include "indexDual.h"

bool IndexDual::matches(const Index &other) {
  IndexDual const *oDual = dynamic_cast<IndexDual const *>(&other);
  return oDual != nullptr &&
         tag1 == oDual->tag1 &&
         tag2 == oDual->tag2;
}

unsigned short IndexDual::hammingDistance(Index const &other) {
  IndexDual const *oDual = dynamic_cast<IndexDual const *>(&other);
  return ham(tag1,oDual->tag1) + ham(tag2,oDual->tag2);
}

size_t IndexDual::length(void) {
  return tag1.length() + tag2.length();
}

std::string const &IndexDual::repr(void) const {
  return tag;
}
