#ifndef __TARGET_H__
#define __TARGET_H__

#include <string>
#include <cstdio>

#include <zlib.h>

class Target {
  public:
    Target(const std::string &dest, const std::string &filename);
    ~Target(void);
    bool open(void);
    void write(char *buffer);
    void close(void);
    
  private:
    std::string makeFilePath(const std::string &dest,const std::string &fn);
    bool wantCompressed(const std::string &fn);

    bool isOpen;
    bool isCompressed;
    std::string path;
    FILE *fdUC;
    gzFile fdGZ;

  friend class TargetFriend;
};

#endif
