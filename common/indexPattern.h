#ifndef __INDEXPATTERN_H__
#define __INDEXPATTERN_H__

#include <string>

class IndexPattern {

  public:
    IndexPattern(std::string pat);
    bool parse(std::string s);
    std::string const &first(void);
    std::string const &second(void);
    std::string const &umi(void);

  protected:
    std::string pattern;
    std::string line;

};

#endif // __INDEXPATTERN_H__
