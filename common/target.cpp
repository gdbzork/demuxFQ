#include <string>
#include <cstdio>
#include <zlib.h>

#include "target.h"

#define GZSUFFIX ".gz"

Target::Target(const std::string &dest,const std::string &filename) {
  isCompressed = wantCompressed(filename);
  isOpen = false;
  path = makeFilePath(dest,filename);
}

bool wantCompressed(const std::string &fn) {
  std::string suffix = fn.substr(fn.length()-3);
  return suffix == GZSUFFIX;
}

bool Target::open(void) {
  bool okay;
  if (isCompressed) {
    fdGZ = gzopen(path.c_str(),"wb");
    okay = fdGZ != NULL;
  } else {
    fdUC = fopen(path.c_str(),"w");
    okay = fdUC != NULL;
  }
  if (okay) {
    isOpen = true;
  }
  return okay;
}

void Target::close(void) {
  if (isCompressed) {
    gzclose(fdGZ);
  } else {
    fsync(fileno(fdUC));
    fclose(fdUC);
  }
  isOpen = false;
}

Target::~Target(void) {
  if (isOpen) {
    close();
  }
}

void Target::write(char *buffer) {
  if (isCompressed) {
    gzprintf(fdGZ,"%s",buffer);
  } else {
    fprintf(fdUC,"%s",buffer);
  }
}

std::string Target::makeFilePath(const std::string &path,const std::string &filename) {
  std::string full_path = path + '/' + filename;
  return full_path;
}

