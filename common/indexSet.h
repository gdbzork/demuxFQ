#ifndef __INDEXSET_H__
#define __INDEXSET_H__

#include <map>
#include <vector>

class IndexSet {

  public:
    Index  &parse(char *buffer);
    void dumpIndices(float threshold);
    int count(Index &i);
    void setPattern(std::string pattern);
    bool unexpected(Index &i);

  protected:
    int tag1pos;
    int tag1len;
    int tag2pos;
    int tag2len;
    int count;

    std::map<std::string,Index *> indices;
    std::map<std::string,int> counts;

    static int split(char *str,char **dest,int max);
    static void revcomp(char *str);
    static char comp(char c);

    bool isUnexpected(std::vector<Index *> *ss);

  friend class IndexSetTest;
};

#endif // __INDEXSET_H__
