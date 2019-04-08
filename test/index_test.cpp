#include "catch.hpp"
#include "config.h"
#include "index.h"
#include "indexSingle.h"
#include "indexDual.h"
#include "indexTester.h"

TEST_CASE("index sanity single","[index]") {
  IndexTester it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  REQUIRE(sample==x->repr());
}

TEST_CASE("index sanity dual","[index]") {
  IndexTester it;
  std::string sample1 = "zork";
  std::string sample2 = "kroz";
  std::string result = "zork+kroz";
  Index *x = it.makeDualIndex(sample1,sample2);
  REQUIRE(result==x->repr());
}

TEST_CASE("index single match","[index]") {
  IndexTester it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  Index *y = it.makeSingleIndex(sample);
  REQUIRE(x->matches(*y));
}

TEST_CASE("index single mismatch","[index]") {
  IndexTester it;
  std::string s1 = "zork";
  std::string s2 = "kroz";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(!x->matches(*y));
}

TEST_CASE("index dual match","[index]") {
  IndexTester it;
  std::string sA = "zork";
  std::string sB = "kroz";
  Index *x = it.makeDualIndex(sA,sB);
  Index *y = it.makeDualIndex(sA,sB);
  REQUIRE(x->matches(*y));
}

TEST_CASE("index dual mismatch","[index]") {
  IndexTester it;
  std::string sA = "zork";
  std::string sB = "kroz";
  Index *x = it.makeDualIndex(sA,sB);
  Index *y = it.makeDualIndex(sB,sA);
  REQUIRE(!x->matches(*y));
}

TEST_CASE("hamming dist internal","[index]") {
  IndexTester it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  REQUIRE(0 == it.ham(x,"alpha","alpha"));
}

TEST_CASE("hamming dist internal length1","[index]") {
  IndexTester it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  REQUIRE(5 == it.ham(x,"alpha","alphabravo"));
}

TEST_CASE("hamming dist internal length2","[index]") {
  IndexTester it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  REQUIRE(5 == it.ham(x,"alphabravo","alpha"));
}

TEST_CASE("hamming dist internal mismatch 1","[index]") {
  IndexTester it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  REQUIRE(1 == it.ham(x,"alpha","alphx"));
}

TEST_CASE("hamming dist internal mismatch 2","[index]") {
  IndexTester it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  REQUIRE(2 == it.ham(x,"blpha","alphx"));
}

TEST_CASE("hamming dist single","[index]") {
  IndexTester it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  Index *y = it.makeSingleIndex(sample);
  REQUIRE(0 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist single length1","[index]") {
  IndexTester it;
  std::string s1 = "alpha";
  std::string s2 = "alphabravo";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(5 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist single length2","[index]") {
  IndexTester it;
  std::string s1 = "alpha";
  std::string s2 = "alphabravo";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(5 == y->hammingDistance(*x));
}

TEST_CASE("hamming dist single mismatch 1","[index]") {
  IndexTester it;
  std::string s1 = "alpha";
  std::string s2 = "alphx";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(1 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist single mismatch 2","[index]") {
  IndexTester it;
  std::string s1 = "blpha";
  std::string s2 = "alphx";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(2 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist single mismatch and length","[index]") {
  IndexTester it;
  std::string s1 = "alphabork";
  std::string s2 = "alphx";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(5 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist double","[index]") {
  IndexTester it;
  std::string sA = "zork";
  std::string sB = "kroz";
  Index *x = it.makeSingleIndex(sA,sB);
  Index *y = it.makeSingleIndex(sA,sB);
  REQUIRE(0 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist double length1","[index]") {
  IndexTester it;
  std::string s1 = "alpha";
  std::string s2 = "alphabravo";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(5 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist double length2","[index]") {
  IndexTester it;
  std::string s1 = "alpha";
  std::string s2 = "alphabravo";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(5 == y->hammingDistance(*x));
}

TEST_CASE("hamming dist double mismatch 1","[index]") {
  IndexTester it;
  std::string s1 = "alpha";
  std::string s2 = "alphx";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(1 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist double mismatch 2","[index]") {
  IndexTester it;
  std::string s1 = "blpha";
  std::string s2 = "alphx";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(2 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist double mismatch and length","[index]") {
  IndexTester it;
  std::string s1 = "alphabork";
  std::string s2 = "alphx";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(5 == x->hammingDistance(*y));
}

