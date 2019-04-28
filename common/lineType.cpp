#include <map>
#include <fstream>
#include <string.h>

#include "lineType.h"

std::string LineTypeChecker::text(LineType tt) {
  switch (tt) {
    case UNIX: return "unix";
    case DOS: return "dos";
    case MAC: return "mac";
    case UNKNOWN: return "unknown";
  }
  return "fell to earth";
}

LineType LineTypeChecker::sget(std::string &fn,unsigned limit) {
  char buffer[limit];
  unsigned count;
  std::ifstream fd;

  fd.open(fn);
  if (fd.fail()) {
    throw LineTypeException("failed to open file");
  }
  fd.read(buffer,limit);
  if (fd.bad()) {
    throw LineTypeException("failed to read file");
  }
  count = fd.gcount();
  return get(buffer,count);
}

LineType LineTypeChecker::fget(std::istream &fd,unsigned limit) {
  char buffer[limit];
  unsigned count;

  fd.read(buffer,limit);
  if (fd.bad()) {
    throw LineTypeException("failed to read stream");
  }
  count = fd.gcount();
  return get(buffer,count);
}

LineType LineTypeChecker::get(char *buffer,unsigned limit) {
  std::map<LineType,int> counts;
  bool skip;
  int bufferMax = strnlen(buffer,limit);

  counts[UNIX] = 0;
  counts[DOS] = 0;
  counts[MAC] = 0;

  skip = false;
  for (unsigned i=0;i<bufferMax-1;i++) {
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
  } else if (buffer[bufferMax-1] == '\r') {
    counts[MAC]++;
  } else if (buffer[bufferMax-1] == '\n') {
    counts[UNIX]++;
  }

  LineType rv;
  if        (counts[UNIX] > 0 && counts[DOS] == 0 && counts[MAC] == 0) {
    rv = UNIX;
  } else if (counts[UNIX] == 0 && counts[DOS] > 0 && counts[MAC] == 0) {
    rv = DOS;
  } else if (counts[UNIX] == 0 && counts[DOS] == 0 && counts[MAC] > 0) {
    rv = MAC;
  } else {
    rv = UNKNOWN;
  }
  return rv;
}
