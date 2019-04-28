#include <cstring>
#include <iostream>
#include "catch.hpp"
#include "config.h"
#include "lineType.h"
#include "lineTypeFriend.h"

TEST_CASE("lineType sanity test","[lineType]") {
  std::string fn = std::string(demux_BINARY_DIR)
                   + std::string("/test/testdata/sampleSheet_nextseq.txt");
  LineType tt = LineTypeChecker::sget(fn);
  REQUIRE(tt == UNIX);
}

TEST_CASE("lineType no-file-found test","[lineType]") {
  std::string fn = std::string(demux_BINARY_DIR)
                   + std::string("/test/testdata/sampleSheet_not_here.txt");
  std::exception_ptr eptr;
  REQUIRE_THROWS_AS(LineTypeChecker::sget(fn),LineTypeException);
}

TEST_CASE("lineType none","[lineType]") {
  char x[] = "this is a test.";
  REQUIRE(LineTypeFriend::get(x) == UNKNOWN);
}

TEST_CASE("lineType mixed","[lineType]") {
  char x[] = "this is a strangely\rmixed\ntest.";
  REQUIRE(LineTypeFriend::get(x) == UNKNOWN);
}

TEST_CASE("lineType unix","[lineType]") {
  char x[] = "this is a\n test.";
  REQUIRE(LineTypeFriend::get(x) == UNIX);
}

TEST_CASE("lineType mac","[lineType]") {
  char x[] = "this is a\rtest.";
  REQUIRE(LineTypeFriend::get(x) == MAC);
}

TEST_CASE("lineType dos","[lineType]") {
  char x[] = "this is a\r\ntest.";
  REQUIRE(LineTypeFriend::get(x) == DOS);
}
