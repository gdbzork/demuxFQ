#include "index.h"

class IndexFriend {

  public:
    Index *makeSingleIndex(std::string &s);
    Index *makeSingleIndex(std::string &s,std::string &u);
    Index *makeDualIndex(std::string &s1,std::string &s2);
    Index *makeDualIndex(std::string &s1,std::string &s2,std::string &u);

    bool matchesIndex(Index *i,std::string &s1);
    bool matchesIndex(Index *i,std::string &s1,std::string &s2);
    bool matchesUMI(Index *i,std::string &u);
    int ham(Index *i,std::string const &s,std::string const &t);
};
