#ifndef FASTQ_H
#define FASTQ_H

#include <string>
#include <istream>

class Fastq {

  public:
    Fastq(const std::string &,int);
    ~Fastq(void);

    bool hasNext(void);
    void next(void);
    const std::string &indexString(void);
    int readCount(void);
    const std::string &source(void);

  private:
    std::istream *fd = NULL;
    std::string filename;
    std::string header;
    int count = 0;
    const int patternLength;
    std::string seq;
    std::string qual;
    std::string third;
};
    
#endif /* FASTQ_H */
