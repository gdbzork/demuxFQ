#include <string>
#include <cstdio>
#include <zlib.h>

#include "target.h"

#define GZSUFFIX ".gz"

Target::Target(std::string const &filename,std::string const &dest,bool compressed,bool noGZ) {
  isCompressed = compressed;
  isOpen = false;
  path = makeFilePath(filename,dest,compressed && !noGZ);
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

std::string Target::makeFilePath(std::string const &base,std::string const &dest,bool wantgz) {
  bool realdest,absolute,hasgz;
  std::string path,suff;
  unsigned suffixLength = strlen(GZSUFFIX);

  realdest = dest != ".";
  absolute = base[0] == '/';
  
  hasgz = base.size() >= suffixLength
          && base.substr(base.size()-suffixLength) == GZSUFFIX;
  wantgz = wantgz && !hasgz;
  suff = wantgz ? GZSUFFIX : "";
  if (absolute) {
    path = base + suff;
  } else {
    if (realdest) {
      path = dest + "/" + base + suff;
    } else {
      path = base + suff;
    }
  }
  return path;
}

