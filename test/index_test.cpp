#include "catch.hpp"
#include "config.h"
#include "index.h"
#include "indexSingle.h"
#include "indexDual.h"
#include "indexFriend.h"

TEST_CASE("index sanity single","[index]") {
  IndexFriend it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  REQUIRE(sample==x->repr());
}

TEST_CASE("index sanity dual","[index]") {
  IndexFriend it;
  std::string sample1 = "zork";
  std::string sample2 = "kroz";
  std::string result = "zork+kroz";
  Index *x = it.makeDualIndex(sample1,sample2);
  REQUIRE(result==x->repr());
}

TEST_CASE("index single match","[index]") {
  IndexFriend it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  Index *y = it.makeSingleIndex(sample);
  REQUIRE(x->matches(*y));
}

TEST_CASE("index single mismatch","[index]") {
  IndexFriend it;
  std::string s1 = "zork";
  std::string s2 = "kroz";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(!x->matches(*y));
}

TEST_CASE("index dual match","[index]") {
  IndexFriend it;
  std::string sA = "zork";
  std::string sB = "kroz";
  Index *x = it.makeDualIndex(sA,sB);
  Index *y = it.makeDualIndex(sA,sB);
  REQUIRE(x->matches(*y));
}

TEST_CASE("index dual mismatch","[index]") {
  IndexFriend it;
  std::string sA = "zork";
  std::string sB = "kroz";
  Index *x = it.makeDualIndex(sA,sB);
  Index *y = it.makeDualIndex(sB,sA);
  REQUIRE(!x->matches(*y));
}

TEST_CASE("hamming dist internal","[index]") {
  IndexFriend it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  REQUIRE(0 == it.ham(x,"alpha","alpha"));
}

TEST_CASE("hamming dist internal length1","[index]") {
  IndexFriend it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  REQUIRE(5 == it.ham(x,"alpha","alphabravo"));
}

TEST_CASE("hamming dist internal length2","[index]") {
  IndexFriend it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  REQUIRE(5 == it.ham(x,"alphabravo","alpha"));
}

TEST_CASE("hamming dist internal mismatch 1","[index]") {
  IndexFriend it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  REQUIRE(1 == it.ham(x,"alpha","alphx"));
}

TEST_CASE("hamming dist internal mismatch 2","[index]") {
  IndexFriend it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  REQUIRE(2 == it.ham(x,"blpha","alphx"));
}

TEST_CASE("hamming dist single","[index]") {
  IndexFriend it;
  std::string sample = "zork";
  Index *x = it.makeSingleIndex(sample);
  Index *y = it.makeSingleIndex(sample);
  REQUIRE(0 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist single length1","[index]") {
  IndexFriend it;
  std::string s1 = "alpha";
  std::string s2 = "alphabravo";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(5 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist single length2","[index]") {
  IndexFriend it;
  std::string s1 = "alpha";
  std::string s2 = "alphabravo";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(5 == y->hammingDistance(*x));
}

TEST_CASE("hamming dist single mismatch 1","[index]") {
  IndexFriend it;
  std::string s1 = "alpha";
  std::string s2 = "alphx";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(1 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist single mismatch 2","[index]") {
  IndexFriend it;
  std::string s1 = "blpha";
  std::string s2 = "alphx";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(2 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist single mismatch and length","[index]") {
  IndexFriend it;
  std::string s1 = "alphabork";
  std::string s2 = "alphx";
  Index *x = it.makeSingleIndex(s1);
  Index *y = it.makeSingleIndex(s2);
  REQUIRE(5 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist double","[index]") {
  IndexFriend it;
  std::string sA = "zork";
  std::string sB = "kroz";
  Index *x = it.makeDualIndex(sA,sB);
  Index *y = it.makeDualIndex(sA,sB);
  REQUIRE(0 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist double length 1","[index]") {
  IndexFriend it;
  std::string sA = "alpha";
  std::string sB1 = "alpha";
  std::string sB2 = "alphab";
  Index *x = it.makeDualIndex(sB1,sA);
  Index *y = it.makeDualIndex(sB2,sA);
  REQUIRE(1 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist double length 2","[index]") {
  IndexFriend it;
  std::string sA = "alpha";
  std::string sB1 = "alpha";
  std::string sB2 = "alphab";
  Index *x = it.makeDualIndex(sA,sB2);
  Index *y = it.makeDualIndex(sA,sB1);
  REQUIRE(1 == y->hammingDistance(*x));
}

TEST_CASE("hamming dist double mismatch 1","[index]") {
  IndexFriend it;
  std::string sA1 = "alqha";
  std::string sB1 = "omega";
  std::string sA2 = "alpha";
  std::string sB2 = "omega";
  Index *x = it.makeDualIndex(sA1,sB1);
  Index *y = it.makeDualIndex(sA2,sB2);
  REQUIRE(1 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist double mismatch 2","[index]") {
  IndexFriend it;
  std::string sA1 = "alqha";
  std::string sB1 = "omega";
  std::string sA2 = "alpha";
  std::string sB2 = "omepa";
  Index *x = it.makeDualIndex(sA1,sB1);
  Index *y = it.makeDualIndex(sA2,sB2);
  REQUIRE(2 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist double mismatch 4","[index]") {
  IndexFriend it;
  std::string sA1 = "alqhabork";
  std::string sB1 = "omegabark";
  std::string sA2 = "alphabork";
  std::string sB2 = "omepabokk";
  Index *x = it.makeDualIndex(sA1,sB1);
  Index *y = it.makeDualIndex(sA2,sB2);
  REQUIRE(4 == x->hammingDistance(*y));
}

TEST_CASE("hamming dist double mismatch and length","[index]") {
  IndexFriend it;
  std::string sA1 = "alqhabork";
  std::string sB1 = "omega";
  std::string sA2 = "alpha";
  std::string sB2 = "omepakrob";
  Index *x = it.makeDualIndex(sA1,sB1);
  Index *y = it.makeDualIndex(sA2,sB2);
  REQUIRE(10 == x->hammingDistance(*y));
}

