#include <string>
#include "target.h"

class TargetFriend {

  public:
    TargetFriend(const Target &t): targ(t) {};
    std::string const &getPath(void);
    bool getOpen(void);
    bool getComp(void);

  private:
    Target targ;
};
