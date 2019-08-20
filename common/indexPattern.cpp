#include "indexPattern.h"

IndexPattern::IndexPattern(std::string pat): pattern{pat} {
  setEndpoints();
  if (!isValid()) {
    throw PatternException(pattern);
  }
}

void IndexPattern::setEndpoints(void) {
  firstStart = pattern.find_first_of(FIRST_INDEX_CHAR);
  firstLength = pattern.find_last_of(FIRST_INDEX_CHAR) - firstStart + 1;
  secondStart = pattern.find_first_of(SECOND_INDEX_CHAR);
  secondLength = pattern.find_last_of(SECOND_INDEX_CHAR) - secondStart + 1;
}

bool IndexPattern::isValid(void) {
  // we expect a single run of 1's, and optionally a single run of 2's
  bool okay = true;
  if (firstStart == std::string::npos) { // no 1's in the string
    okay = false;
  } else {
    for (int i=firstStart;i<firstStart+firstLength;i++) {
      if (pattern[i] != FIRST_INDEX_CHAR) {
        okay = false;
      }
    }
  }
  if (okay && secondStart != std::string::npos) {
    for (int i=secondStart;i<secondStart+secondLength;i++) {
      if (pattern[i] != SECOND_INDEX_CHAR) {
        okay = false;
      }
    }
  }
  return okay;
}

bool IndexPattern::matches(const std::string &line) {
  int start = line.length() - pattern.length();
  index1.assign(line,start+firstStart,firstLength);
  if (secondStart != std::string::npos) {
    index2.assign(line,start+secondStart,secondLength);
  }
  return true;
}

std::string const &IndexPattern::first(void) {
  return index1;
}

std::string const &IndexPattern::second(void) {
  return index2;
}
