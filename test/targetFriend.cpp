#include <string>
#include "target.h"
#include "targetFriend.h"

std::string const &TargetFriend::getPath(void) {
  return targ.path;
}

bool TargetFriend::getOpen(void) {
  return targ.isOpen;
}

bool TargetFriend::getComp(void) {
  return targ.isCompressed;
}
