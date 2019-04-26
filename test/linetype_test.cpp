#include "catch.hpp"
#include "config.h"
#include "lineType.h"

TEST_CASE("lineType sanity test","[lineType]") {
  char fn[100] = demux_BINARY_DIR;
  strcat(fn,"/test/testdata/sampleSheet_nextseq.txt");
  TextType tt = TextTypeChecker.sget(fn);
  REQUIRE(tt.text != nullptr);
}

