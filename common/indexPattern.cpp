#include "indexPattern.h"

IndexPattern::IndexPattern(std::string pat) {
  // Nothing happens here.
}

bool IndexPattern::parse(std::string s) {
  return false;
}

std::string const &IndexPattern::first(void) {
  return pattern;
}

std::string const &IndexPattern::second(void) {
  return pattern;
}

std::string const &IndexPattern::umi(void) {
  return pattern;
}
