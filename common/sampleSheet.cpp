#include <fstream>
#include <ctype.h>

#include "sampleSheet.h"
#include "util.h"
#include "lineType.h"

#define MAXLINE 2048

char *SampleSheet::stripWhiteSpace(char *str) {
  int slen,start,end;

  slen = strlen(str);
  start = 0;
  while (start < slen && isspace(str[start])) {
    start++;
  }
  end = slen-1;
  while (end > start && isspace(str[end])) {
    end--;
  }
  str[end+1] = '\0';
  if (start > 0) {
    memmove(str,str+start,end-start+2);
  }
  return str;
}

std::string SampleSheet::getName(char *buffer,std::string &sample,bool hasSample) {
  int i;
  if (hasSample) {
    i = strlen(buffer) - 1;
    while (i>=0) {
      if (isspace(buffer[i])) {
        sample = std::string(buffer + i + 1);
        buffer[i] = '\0';
        break;
      }
      i--;
    }
  }
  i = strlen(buffer) - 1;
  while (i>=0) {
    if (isspace(buffer[i])) {
      return std::string(buffer + i + 1);
    }
    i--;
  }
  return "";
}

SampleSheet *SampleSheet::load(char *inFN,bool hasSamples,bool reverse_second) {
  SampleSheet *sheet;
  char buffer[MAXLINE];
  std::vector<std::string> row;
  int count;
  std::string name;
  std::string sample;
  Index *ind;
  std::ifstream inFD;
  TextType tt;
  char termChar;
  
  tt = TextTypeChecker::sget(inFN);
  if (tt == UNIX || tt == DOS) {
    termChar = '\n';
  } else if (tt == MAC) {
    termChar = '\r';
  } else {
    log(std::cerr,"load","cannot determine line termination type");
    return NULL;
  }

  inFD.open(inFN);
  if (inFD.bad() || !inFD.is_open()) {
    log(std::cerr,"load","failed to open sample sheet");
    return NULL;
  }
  count = 0;
  sheet = NULL;
  inFD.getline(buffer,MAXLINE,termChar);

  while (!inFD.eof() && !inFD.fail()) {
    stripWhiteSpace(buffer);
    if (strlen(buffer) == 0 || buffer[0] == '#') {
      inFD.getline(buffer,MAXLINE,termChar);
      continue;
    }
    count++;
    name = getName(buffer,sample,hasSamples);
    ind = Index::indexFromSampleSheet(buffer,false,reverse_second);
    if (ind == NULL) {
      log(std::cerr,"load",count,"error in sample sheet");
      return NULL;
    }
    if (hasSamples) {
      ind->setSample(sample);
    }
    if (sheet == NULL) {
      sheet = new SampleSheet();
    }
    sheet->add(name,ind);
    inFD.getline(buffer,MAXLINE,termChar);
  }
  if (!inFD.eof()) {
    log(std::cerr,"load","Unknown error loading sample sheet");
    return NULL;
  }
  return sheet;
}

void SampleSheet::add(std::string const &fn,Index *ind) {
  indices.push_back(ind);
  sampleFN.push_back(fn);
  count++;
}

int SampleSheet::check(Index const &read,int stringency) {
  int p;
  for (p=0;p<count;p++) {
    if (indices[p]->isMatch(read,stringency)) {
      return p;
    }
  }
  return -1;
}

void SampleSheet::dump(std::ostream &destination) {
  int i;
  destination << "Sample Sheet: " << count << " rows:" << std::endl;
  for (i=0;i<count;i++) {
    destination << indices[i]->repr() << "\t" << sampleFN[i] << std::endl;
  }
}

std::string const &SampleSheet::getFN(int position) {
  return sampleFN[position];
}

Index *SampleSheet::getIndex(int position) {
  return indices[position];
}

int SampleSheet::rows(void) {
  return count;
}

int SampleSheet::minHammingDistance(void) {
  int i,j;
  int minDist = indices[0]->length();

  for (i=0;i<count-1;i++) {
    for (j=i+1;j<count;j++) {
      int d = indices[i]->hammingDistance(*indices[j]);
      if (d < minDist) {
        minDist = d;
      }
    }
  }
  return minDist;
}

bool SampleSheet::isDual(void) {
  return indices[0]->isDual();
}

std::vector<Index*>* SampleSheet::getIndices(void) {
  return &indices;
}
