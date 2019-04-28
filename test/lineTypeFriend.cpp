#include "lineType.h"
#include "lineTypeFriend.h"

LineType LineTypeFriend::get(char *buffer, unsigned limit) {
  return LineTypeChecker::get(buffer,limit);
}

