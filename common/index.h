#ifndef __INDEX_H__
#define __INDEX_H__

#include <string>

class Index {

  public:
    virtual bool matches(Index const &other) = 0;
    virtual unsigned short hammingDistance(Index const &other) = 0;
    virtual size_t length(void) = 0;
    virtual std::string const &repr(void) const = 0;
    std::string const &umi(void);

    static int mismatchesAllowed; // default 0

  protected:
    std::string umiS;

    int ham(std::string const &s,std::string const &t);
    void revcomp(std::string &in);

    Index():umiS("") {};
    Index(std::string u):umiS(u) {};
    virtual ~Index() {};

  friend class IndexSet;
  friend class IndexTester;
};

#endif
