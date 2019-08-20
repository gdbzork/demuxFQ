#include "catch.hpp"
#include "indexPattern.h"
#include "indexPatternFriend.h"

TEST_CASE("indexPattern sanity test","[indexPattern]") {
  REQUIRE_NOTHROW(IndexPattern("11111111"));
}

TEST_CASE("dual pattern endpoints set test","[indexPattern]") {
  IndexPattern x = IndexPattern("11111111X22222222");
  IndexPatternFriend ipf = IndexPatternFriend(x);
  REQUIRE(ipf.getFirstStart() == 0);
  REQUIRE(ipf.getFirstLength() == 8);
  REQUIRE(ipf.getSecondStart() == 9);
  REQUIRE(ipf.getSecondLength() == 8);
}


TEST_CASE("dual pattern sanity test","[indexPattern]") {
  IndexPattern x = IndexPattern("11111111X22222222");
  IndexPatternFriend ipf = IndexPatternFriend(x);
  REQUIRE(ipf.getValid());
  REQUIRE_NOTHROW(IndexPattern("11111111X22222222"));
}

TEST_CASE("indexPattern invalid test","[indexPattern]") {
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

TEST_CASE("null string for pattern","[indexPattern]") {
  std::string pattern;
  REQUIRE_THROWS_AS(IndexPattern(pattern),PatternException);
}

TEST_CASE("Find first index","[indexPattern]") {
  IndexPattern ip("11111zorkXX");
  std::string ind = "alphaABCDEzork99";
  REQUIRE(ip.matches(ind));
  REQUIRE(ip.first() == "ABCDE");
}

TEST_CASE("Find second index","[indexPattern]") {
  IndexPattern ip("11111zork22222XX");
  std::string ind = "alphaABCDEzorkFGHIJ99";
  REQUIRE(ip.matches(ind));
  REQUIRE(ip.second() == "FGHIJ");
}

TEST_CASE("Detect non-matching string","[indexPattern]") {
  IndexPattern ip("11111zorkXX");
  std::string ind = "alphaABCDEzark99";
  REQUIRE(ip.matches(ind) == false);
}

