#include "catch.hpp"
#include "config.h"
#include "index.h"
#include "indexSingle.h"

TEST_CASE("index sanity","[index]") {
  Index *x = new IndexSingle("zork");
  REQUIRE("zork"==x->repr());
}
