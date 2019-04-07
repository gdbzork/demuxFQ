#ifndef __INDEXDUAL_H__
#define __INDEXDUAL_H__

#include "index.h"

class IndexDual: public Index {

  public:
    bool matches(Index const &other);
    unsigned short hammingDistance(Index const &other);
    size_t length(void);
    std::string const &repr(void);


  protected:
    std::string tag1;
    std::string tag2;
    std::string tag;

    IndexDual(std::string t1,std::string t2):tag1(t1),tag2(t2) {};
    IndexDual(std::string t1,std::string t2,std::string u): Index(u),
                                                            tag1(t1),
                                                            tag2(t2) {};
    virtual ~IndexDual() {};

  friend class IndexTester;
};

#endif // __INDEXDUAL_H__
