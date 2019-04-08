#include "index.h"
#include "indexSingle.h"

bool IndexSingle::matches(const Index &other) {
  IndexSingle const *oSingle = dynamic_cast<IndexSingle const *>(&other);
  return oSingle != nullptr &&
         tag == oSingle->tag;
}

unsigned short IndexSingle::hammingDistance(Index const &other) {
  IndexSingle const *oSingle = dynamic_cast<IndexSingle const *>(&other);
  return ham(tag,oSingle->tag);
}

size_t IndexSingle::length(void) {
  return tag.length();
}

std::string const &IndexSingle::repr(void) const {
  return tag;
}
