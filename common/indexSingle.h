#ifndef __INDEXSINGLE_H__
#define __INDEXSINGLE_H__

#include "index.h"

class IndexSingle: public Index {

  public:
    bool matches(Index const &other);
    unsigned short hammingDistance(Index const &other);
    size_t length(void);
    std::string const &repr(void);


  protected:
    std::string tag;

    IndexSingle(std::string t):tag(t) {};
    IndexSingle(std::string t,std::string u): Index(u), tag(t) {};
    virtual ~IndexSingle() {};

  friend class IndexTester;
};

#endif // __INDEXSINGLE_H__
