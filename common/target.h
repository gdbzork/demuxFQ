#ifndef __TARGET_H__
#define __TARGET_H__

#include <string.h>
#include <cstdio>

#include <zlib.h>

class Target {
  public:
    Target(std::string const &filename,std::string const &dest,bool compressed,bool noGZ);
    ~Target(void);
    bool open(void);
    void write(char *buffer);
    void close(void);
    
  private:
    std::string makeFilePath(std::string const &fn,std::string const &dest,bool wantGZ);

    bool isOpen;
    bool isCompressed;
    std::string path;
    FILE *fdUC;
    gzFile fdGZ;

  friend class TargetTest;
};

#endif
