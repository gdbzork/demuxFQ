#ifndef __INDEX_H__
#define __INDEX_H__

class Index {

  public:
    static Index& parse(char *buffer);
    static void setPattern(std::string pattern);
    
    bool matches(Index const &other);
    int hammingDistance(Index const &other);
    size_type length(void);
    std::string repr(void);

    static char delimiter = ':';
    static int mismatchesAllowed = 0;

  protected:
    static std::string pattern = "11111111UUUUUUUUU+22222222";
    static int startSecond = 18;
    static bool dual = true;
    std::string tag;

//    static int split(char *str,char **dest,int max);
//    static void revcomp(char *str);
//    static char comp(char c);

    Index(std::string s):tag(s) {};

  friend class IndexTest;
};

#endif
