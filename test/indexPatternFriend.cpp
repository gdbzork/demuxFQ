#include "indexPattern.h"
#include "indexPatternFriend.h"

std::string const &IndexPatternFriend::getFirst(void) {
  return indexPat.index1;
}

std::string const &IndexPatternFriend::getSecond(void) {
  return indexPat.index2;
}

int IndexPatternFriend::getFirstStart(void) {
  return indexPat.firstStart;
}

int IndexPatternFriend::getFirstLength(void) {
  return indexPat.firstLength;
}

int IndexPatternFriend::getSecondStart(void) {
  return indexPat.secondStart;
}

int IndexPatternFriend::getSecondLength(void) {
  return indexPat.secondLength;
}

bool IndexPatternFriend::getValid(void) {
  return indexPat.isValid();
}
