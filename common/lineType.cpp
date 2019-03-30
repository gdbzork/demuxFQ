#include <map>
#include <fstream>
#include <string.h>

#include "lineType.h"

std::string TextTypeChecker::text(TextType tt) {
  switch (tt) {
    case UNIX: return "unix";
    case DOS: return "dos";
    case MAC: return "mac";
    case MIXED: return "mixed";
    case UNKNOWN: return "unknown";
    case FAIL: return "failed to detect";
  }
  return "fell to earth";
}

TextType TextTypeChecker::sget(char *fn,unsigned limit) {
  char buffer[limit];
  unsigned count;
  std::ifstream fd;

  fd.open(fn);
  if (fd.fail()) {
    return FAIL;
  }
  fd.read(buffer,limit);
  if (fd.bad()) {
    return FAIL;
  }
  count = fd.gcount();
  return get(buffer,count);
}

TextType TextTypeChecker::fget(std::istream &fd,unsigned limit) {
  char buffer[limit];
  unsigned count;

  fd.read(buffer,limit);
  if (fd.bad()) {
    return FAIL;
  }
  count = fd.gcount();
  return get(buffer,count);
}

TextType TextTypeChecker::get(char *buffer,unsigned limit) {
  std::map<TextType,int> counts;
  bool skip;

  counts[UNIX] = 0;
  counts[DOS] = 0;
  counts[MAC] = 0;

  skip = false;
  for (unsigned i=0;i<limit-1;i++) {
    if (skip) {
      skip = false;
    } else if (buffer[i] == '\r') {
      if (buffer[i+1] == '\n') {
        counts[DOS]++;
        skip = true;
      } else {
        counts[MAC]++;
      }

    } else if (buffer[i] == '\n') {
      counts[UNIX]++;
    }
  }
  // look at last character
  if (skip) {
    skip = false;
  } else if (buffer[limit-1] == '\r') {
    counts[MAC]++;
  } else if (buffer[limit-1] == '\n') {
    counts[UNIX]++;
  }

  TextType rv;
  if        (counts[UNIX] > 0 && counts[DOS] == 0 && counts[MAC] == 0) {
    rv = UNIX;
  } else if (counts[UNIX] == 0 && counts[DOS] > 0 && counts[MAC] == 0) {
    rv = DOS;
  } else if (counts[UNIX] == 0 && counts[DOS] == 0 && counts[MAC] > 0) {
    rv = MAC;
  } else if (counts[UNIX] == 0 && counts[DOS] == 0 && counts[MAC] == 0) {
    rv = UNKNOWN;
  } else {
    rv = MIXED;
  }
  return rv;
}
