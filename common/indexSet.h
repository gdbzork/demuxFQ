#ifndef __INDEX_H__
#define __INDEX_H__

#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>

class Index {
  public:
    static Index *indexFromFastqHeader(char *buffer,bool duplicateAllowed=true);
    static Index *indexFromSampleSheet(char *buffer,bool duplicateAllowed=false,bool reverse_second=false);
    static void dumpIndices(std::vector<Index*> *ss,std::vector<Index*> &unexpected,float threshold,FILE *fd);
    static int getCount(Index *i);
    static void clearStaticData(void);

    Index(std::string s):tag1(s),tag2("") {
      tag1len = tag1.length();
      tag2len = 0;
      sampleName = "";
    };
    Index(std::string s1,std::string s2):tag1(s1),tag2(s2) {
      tag1len = tag1.length();
      tag2len = tag2.length();
      sampleName = "";
    };
    void setSample(std::string &sample) {
      sampleName = sample;
    }
    bool isMatch(Index const &other,int stringency,bool allowN=false);
    int hammingDistance(Index const &other);
    int length(void);
    bool isDual(void);
    std::string repr(void);
    std::string getName(void) { return sampleName; };
    static void clearCache(void);
    static void zeroCounts(void);
    static void setParams(bool illumina,int lenFirst);

  protected:
    std::string tag1;
    std::string tag2;
    int tag1len;
    int tag2len;
    std::string sampleName;

    static std::map<std::string,Index *> indices;
    static std::map<std::string,int> counts;
    static bool isIllumina;
    static int lenFirstParam;
    static int lenSecondParam;
    static bool firstWasSet;
    static bool isDualFlag;

    static int split(char *str,char **dest,int max);
    static void revcomp(char *str);
    static char comp(char c);

    bool isUnexpected(std::vector<Index *> *ss);

  friend class IndexTest;
};

#endif
