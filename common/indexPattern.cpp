#include "indexPattern.h"

IndexPattern::IndexPattern(std::string pat): pattern{pat} {
  setEndpoints();
  if (!valid()) {
    throw PatternException(pattern);
  }
}

void IndexPattern::setEndpoints(void) {
  firstStart = pattern.find_first_of(FIRST_INDEX_CHAR);
  firstEnd = pattern.find_last_of(FIRST_INDEX_CHAR);
  secondStart = pattern.find_first_of(SECOND_INDEX_CHAR);
  secondEnd = pattern.find_last_of(SECOND_INDEX_CHAR);
}

bool IndexPattern::valid(void) {
  // we expect a single run of 1's, and optionally a single run of 2's
  bool okay = true;
  if (firstStart == std::string::npos) { // no 1's in the string
    okay = false;
  } else {
    for (int i=firstStart;i<=firstEnd;i++) {
      if (pattern[i] != FIRST_INDEX_CHAR) {
        okay = false;
      }
    }
  }
  if (okay && secondStart != std::string::npos) {
    for (int i=secondStart;i<=secondEnd;i++) {
      if (pattern[i] != SECOND_INDEX_CHAR) {
        okay = false;
      }
    }
  }
  return okay;
}

bool IndexPattern::parse(std::string s) {
  line = s;
  return false;
}

std::string const &IndexPattern::first(void) {
  return pattern;
}

std::string const &IndexPattern::second(void) {
  return pattern;
}
