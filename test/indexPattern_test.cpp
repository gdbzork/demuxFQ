#include "catch.hpp"
#include "indexPattern.h"

TEST_CASE("indexPattern sanity test","[indexPattern]") {
  REQUIRE_NOTHROW(IndexPattern("11111111"));
}

TEST_CASE("dual pattern sanity test","[indexPattern]") {
  REQUIRE_NOTHROW(IndexPattern("11111111X22222222"));
}

TEST_CASE("indexPattern valid test","[indexPattern]") {
  REQUIRE_THROWS_AS(IndexPattern("111X11111"),PatternException);
}

TEST_CASE("indexPattern no pattern","[indexPattern]") {
  REQUIRE_THROWS_AS(IndexPattern("In the beginning"),PatternException);
}

TEST_CASE("Index Exceptions","[Exceptions]") {
  std::string pattern = "12345678";
  std::string expected = "Index parse error: '" + pattern + "'";
  IndexException *ie = new IndexException(pattern);
  std::string result = std::string(ie->what());
  REQUIRE(result == expected);
}

TEST_CASE("Pattern Exceptions","[Exceptions]") {
  std::string pattern = "12345678";
  std::string expected = "Illegal pattern: '" + pattern + "'";
  PatternException *ie = new PatternException(pattern);
  std::string result = std::string(ie->what());
  REQUIRE(result == expected);
}
