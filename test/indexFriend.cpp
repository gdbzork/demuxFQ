#include "index.h"
#include "indexSingle.h"
#include "indexDual.h"
#include "indexFriend.h"

Index *IndexFriend::makeSingleIndex(std::string &s) {
  return new IndexSingle(s);
}

Index *IndexFriend::makeSingleIndex(std::string &s,std::string &u) {
  return new IndexSingle(s,u);
}

Index *IndexFriend::makeDualIndex(std::string &s1,std::string &s2) {

  return new IndexDual(s1,s2);
}

Index *IndexFriend::makeDualIndex(std::string &s1,std::string &s2,std::string &u) {
  return new IndexDual(s1,s2,u);
}

bool IndexFriend::matchesIndex(Index *i,std::string &s) {
  bool m;
  try {
    IndexSingle *is = dynamic_cast<IndexSingle*>(i);
    m = is->tag == s;
  } catch (...) {
    m = false;
  }
  return m;
}

bool IndexFriend::matchesIndex(Index *i,std::string &s1,std::string &s2) {
  bool m = false;
/*
  try {
    IndexDual *is = dynamic_cast<IndexDual*>(i);
    m = is->tag1 == s1 && is->tag2 == s2;
  } catch (...) {
    m = false;
  }
*/
  return m;
}
  
bool IndexFriend::matchesUMI(Index *i,std::string &u) {
  return u == i->umiS;
}

int IndexFriend::ham(Index *i,std::string const &s,std::string const &t) {
  return i->ham(s,t);
}
