#include "indexPattern.h"

class IndexPatternFriend {

  public:
    IndexPatternFriend(const IndexPattern &ip): indexPat(ip) {};
    std::string const &getFirst(void);
    std::string const &getSecond(void);
    int getFirstStart(void);
    int getFirstLength(void);
    int getSecondStart(void);
    int getSecondLength(void);
    bool getValid(void);

  private:
    IndexPattern indexPat;
};
