#ifndef __SAMPLE_SHEET_H__
#define __SAMPLE_SHEET_H__

#include <vector>
#include <iostream>
#include "index.h"

class SampleSheet {
  public:
    static SampleSheet *load(char *src,bool samples,bool reverse_second);

    virtual ~SampleSheet() { };
    virtual void add(std::string const &fn,Index *ind);
    int check(Index const &read,int stringency);
    virtual bool isDual(void);
    virtual void dump(std::ostream &destination);
    virtual std::string const &getFN(int position);
    virtual Index *getIndex(int position);
    int rows(void);
    int minHammingDistance(void);
    std::vector<Index*> *getIndices(void);

  private:
    SampleSheet(void):count(0) {};
    static char *stripWhiteSpace(char *str);
    static std::string getName(char *buffer,std::string &sample,bool hasSample);

    std::vector<Index*> indices;
    std::vector<std::string> sampleFN;
    int count;
    bool hasSampleNames;

  friend class SampleSheetTest;
};

#endif
