#include "fastq.h"

Fastq::Fastq(const std::string &fn,int pLen):filename(fn),patternLength(pLen) {
  // open file here
  return;
}

bool Fastq::hasNext(void) {
  return false;
}

void Fastq::next(void) {
}

const std::string &Fastq::indexString(void) {
  return header;
}

int Fastq::readCount(void) {
  return 0;
}

const std::string &Fastq::source(void) {
  return filename;
}
