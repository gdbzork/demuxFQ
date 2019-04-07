#include "index.h"

class IndexSingle: public Index {

  public:
    IndexSingle(std::string t):tag(t) {};
    bool matches(Index const &other);
    unsigned short hammingDistance(Index const &other);
    size_t length(void);
    std::string const &repr(void);


  protected:
    std::string tag;

};
