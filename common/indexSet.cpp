#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include "index.h"
#include "util.h"

char IndexSet::delimiter = ':';
int IndexSet::mismatchesAllowed = 0;
std::string IndexSet::pattern = "11111111UUUUUUUUU+22222222";

std::map<std::string,Index *> Index::indices;
std::map<std::string,int> Index::counts;
bool Index::isIllumina;
int Index::lenFirstParam;
int Index::lenSecondParam;
bool Index::firstWasSet;
bool Index::isDualFlag;

int Index::split(char *str,char **dest,int max) {
  int index = 0,inspace;
  char *start = str;
  if (str == NULL) {
    return 0;
  }
  inspace = isspace(*str);
  while (*str != '\0' && index < max) {
    if (isspace(*str)) {
      if (!inspace) {
        dest[index++] = start;
        inspace = 1;
      }
      if (index < max) {
        *str = '\0';
      }
    } else {
      if (inspace) {
        start = str;
        inspace = 0;
      }
    }
    str++;
  }
  if (!inspace && index < max) {
    dest[index++] = start;
  }
  return index;
}

char Index::comp(char c) {
  switch(c) {
    case 'A': c = 'T'; break;
    case 'C': c = 'G'; break;
    case 'G': c = 'C'; break;
    case 'T': c = 'A'; break;
  }
  return c;
}

void Index::revcomp(char *str) {
  int len, hlen, i, k;
  char temp; 
  if (str == 0 || *str == 0) {
    return;
  }
  len = strlen(str);
  hlen = len/2;
  for(i=0,k=len-1; i<hlen; i++,k--) {
    temp = str[k];
    str[k] = comp(str[i]);
    str[i] = comp(temp);
  }
  if (i==k) {
    str[i] = comp(str[i]);
  }
  return;
}

void Index::setParams(bool illumina,int lenFirst) {
  isIllumina = illumina;
  lenFirstParam = lenFirst;
  firstWasSet = lenFirst > -1;
}

Index *Index::indexFromFastqHeader(char *buffer,bool duplicateAllowed) {
  char *tagHead,*tagTail;
  std::string tag1,tag2;
  std::string representation;
  Index *result;

  if (isIllumina) {
    tagHead = strrchr(buffer,':');
    if (tagHead == NULL) { // colon not found
      log(std::cerr,"indexFromFastqHeader","failed to find ':' in fastq header, probable corrupt fastq file");
      return NULL;
    }
    tagHead += 1;
    if (isDualFlag) {
      if (firstWasSet) {
        tag1 = std::string(tagHead,lenFirstParam);
        tag2 = std::string(tagHead+lenFirstParam);
      } else if (strlen(tagHead) == (unsigned)(lenFirstParam + lenSecondParam)) {
        tag1 = std::string(tagHead,lenFirstParam);
        tag2 = std::string(tagHead+lenFirstParam);
      } else {
        char *plusPos = strchr(tagHead,'+');
        if (plusPos != NULL) {
          lenFirstParam = plusPos - tagHead;
          tag1 = std::string(tagHead,lenFirstParam);
          tag2 = std::string(tagHead+lenFirstParam+1);
        } else {
          log(std::cerr,"indexFromFastqHeader","Sample sheet vs fastq header mismatch and length of 1st index not given via -l (and '+' separator not found)");
          return NULL;
        }
      }
      representation = tag1 + "," + tag2;
    } else {
      tag1 = std::string(tagHead);
      tag2 = "";
      representation = tag1;
    }
  } else {
    tagHead = strchr(buffer,'#');
    if (tagHead == NULL) { // octothorpe not found
      log(std::cerr,"indexFromFastqHeader","failed to find '#' in fastq header, probable corrupt fastq file");
      return NULL;
    }
    tagHead += 1;
    tagTail = strpbrk(tagHead,"/#");
    if (tagTail == NULL) {
      tag1 = std::string(tagHead);
      tag2 = "";
      representation = tag1;
    } else {
      tag1 = std::string(tagHead,tagTail-tagHead);
      if (*tagTail == '#') { // it's a dual index
        char *tag2head,*tag2tail;
        tag2head = tagTail + 1;
        tag2tail = strchr(tag2head,'/');
        if (tag2tail == NULL) {
          tag2 = std::string(tag2head);
        } else {
          tag2 = std::string(tag2head,tag2tail-tag2head);
        }
        isDualFlag = true;
        representation = tag1 + "," + tag2;
      } else {
        tag2 = "";
        representation = tag1;
      }
    }
  }
  if (indices.count(representation) > 0) {
    if (duplicateAllowed) {
      result = indices[representation];
      counts[representation] = counts[representation] + 1;
    } else {
      result = NULL;
    }
  } else {
    if (isDualFlag) {
      result = new Index(tag1,tag2);
    } else {
      result = new Index(tag1);
    }
    indices[representation] = result;
    counts[representation] = 1;
  }
  return result;
}

Index *Index::indexFromSampleSheet(char *buffer,bool duplicateAllowed,bool reverse_second) {
  int fields;
  int maxTokens = 4;
  char *tokens[4];
  Index *result;
  std::string representation;

  fields = split(buffer,tokens,maxTokens);
  if (fields < 2 || fields > 3) {
    log(std::cerr,"indexFromSampleSheet","sample sheet line should have 2 or 3 tokens (or 3-4 if sample descriptions included)");
    return NULL;
  }
  if (fields == 2) {
    representation = std::string(tokens[0]);
    isDualFlag = false;
  } else {
    representation = std::string(tokens[0]) + "," + std::string(tokens[1]);
    isDualFlag = true;
    int len1st = strlen(tokens[0]);
    if (!firstWasSet) {
      if (lenFirstParam < len1st) {
        lenFirstParam = len1st;
      }
    } else if (lenFirstParam < len1st) {
      log(std::cerr,"indexFromSampleSheet","index in sample sheet longer than specified length of 1st index");
      return NULL;
    }
    int len2nd = strlen(tokens[1]);
    if (lenSecondParam < len2nd) {
      lenSecondParam = len2nd;
    }
  }
  if (indices.count(representation) > 0) {
    if (duplicateAllowed) {
      result = indices[representation];
      counts[representation] = counts[representation] + 1;
    } else {
      log(std::cerr,"indexFromSampleSheet","duplicate index in sample sheet");
      return NULL;
    }
  } else {
    if (fields == 2) {
      result = new Index(std::string(tokens[0]));
    } else {
      if (reverse_second) {
        revcomp(tokens[1]);
      }
      result = new Index(std::string(tokens[0]),std::string(tokens[1]));
    }
    indices[representation] = result;
    counts[representation] = 1;
  }
  return result;
}

bool Index::isUnexpected(std::vector<Index *> *ss) {
  std::vector<Index *>::iterator itss;
  bool unexpected = true;
  for (itss=ss->begin(); itss!=ss->end(); itss++) {
    if ((*itss)->isMatch(*this,0,true)) {
      unexpected = false;
      break;
    }
  }
  return unexpected;
}

void Index::dumpIndices(std::vector<Index*> *ss,std::vector<Index *> &unexpected,float threshold,FILE *dest) {
  std::map<std::string,int>::iterator it;
  int total = 0;
 
//  dest << counts.size() << " distinct codes" << std::endl;
  fprintf(dest,"%lu distinct codes\n",counts.size());
  for (it=counts.begin(); it!=counts.end(); it++) {
    total += it->second;
  }
  for (it=counts.begin(); it!=counts.end(); it++) {
    int c = it->second;
    double frac = (double) c / (double) total;
    if (frac > threshold) {
      Index *m = indices[it->first];
      if (ss != NULL && m->isUnexpected(ss)) {
        unexpected.push_back(m);
      } else {
 //       dest << std::setw(9) << c << "\t" << it->first << std::endl;
        fprintf(dest,"%9d\t%s\n",c,it->first.c_str());
      }
    }
  }
}

void Index::clearCache(void) {
  indices.clear();
  counts.clear();
}

void Index::zeroCounts(void) {
  std::map<std::string,int>::iterator it;
  for (it=counts.begin(); it!=counts.end(); it++) {
    counts[it->first] = 0;
  }
}

bool Index::isMatch(Index const &other,int stringency,bool allowN) {
  int m1 = 0,m2 = 0;

  if (other.tag1len < tag1len || other.tag2len < tag2len) {
    // won't match against a shorter tag
    return false;
  }
  for (int i=0;i<tag1len;i++) {
    if (tag1[i] == other.tag1[i] || (allowN && other.tag1[i] == 'N')) {
      m1++;
    }
  }
  for (int i=0;i<tag2len;i++) { // skips if tag2len == 0, i.e. single index
    if (tag2[i] == other.tag2[i] || (allowN && other.tag1[i] == 'N')) {
      m2++;
    }
  }
  return m1 >= tag1len - stringency
         && (tag2len == 0 || m2 >= tag2len - stringency);
}

int Index::hammingDistance(Index const &other) {
  int i,d1 = 0,d2 = 0;
  int minlen1 = std::min(tag1len,other.tag1len);
  int minlen2 = std::min(tag2len,other.tag2len);

  for (i=0;i<minlen1;i++) {
    d1 += (tag1[i] == other.tag1[i]) ? 0 : 1;
  }
  for (i=0;i<minlen2;i++) {
    d2 += (tag2[i] == other.tag2[i]) ? 0 : 1;
  }
  return d1 + d2;
}

int Index::length(void) {
  return tag1len + tag2len;
}

bool Index::isDual(void) {
  return tag2len > 0;
}

std::string Index::repr(void) {
  std::string result;
  if (tag2len == 0) {
    result = tag1;
  } else {
    result = tag1 + "," + tag2;
  }
  return result;
}

int Index::getCount(Index *i) {
  return counts[i->repr()];
}

void Index::clearStaticData(void) {
  indices.clear();
  counts.clear();
  isIllumina = false;
  lenFirstParam = 0;
  lenSecondParam = 0;
  firstWasSet = false;
  isDualFlag = false;
}
