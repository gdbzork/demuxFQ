#include <algorithm>
#include <string>
#include "index.h"

int Index::mismatchesAllowed = 0;

char nucComp(char c) {
  switch(c) {
    case 'A': c = 'T'; break;
    case 'C': c = 'G'; break;
    case 'G': c = 'C'; break;
    case 'T': c = 'A'; break;
  }
  return c;
}

void Index::revcomp(std::string &in) {
/*
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
*/
  transform(begin(in),end(in),begin(in),nucComp);
  return;
}

/*
bool Index::matches(Index const &other) {
  int m = 0;
  bool okay = true;

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
  int i,d = 0;
  int minlen = std::min(tag.length(),other.tag.length());

  for (i=0;i<minlen;i++) {
    d1 += (tag[i] == other.tag[i]) ? 0 : 1;
  }
  return d1 + d2;
}
*/

size_t Index::length(void) {
  return tag.length();
}

std::string const &Index::repr(void) {
  return tag;
}

std::string const &Index::umiTag(void) {
  return umi;
}
