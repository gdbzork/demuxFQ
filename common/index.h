#ifndef __INDEX_H__
#define __INDEX_H__

#include <string>

class Index {

  public:
    virtual bool matches(Index const &other) = 0;
    virtual unsigned short hammingDistance(Index const &other) = 0;
    size_t length(void);
    std::string const &repr(void);
    std::string const &umiTag(void);

    static int mismatchesAllowed; // default 0

  protected:
    static std::string pattern;
    std::string tag;
    std::string umi;

    void revcomp(std::string &in);

    Index(std::string s):tag(s) {};

  friend class IndexSet;
  friend class IndexTest;
};

#endif
