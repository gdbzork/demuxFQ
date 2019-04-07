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
