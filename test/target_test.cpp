#include "catch.hpp"
#include "config.h"
#include "target.h"
#include "targetFriend.h"

TEST_CASE("gz suffix present","[target]") {
  std::string fn = "zork.fq.gz";
  std::string path = "/this/is/a/test";
  Target targ(path,fn);
  TargetFriend tf(targ);
  bool comp = tf.getComp();
  REQUIRE(comp == true);
}

TEST_CASE("gz suffix absent","[target]") {
  std::string fn = "zork.fq";
  std::string path = "/this/is/a/test";
  Target targ(path,fn);
  TargetFriend tf(targ);
  bool comp = tf.getComp();
  REQUIRE(comp == false);
}

TEST_CASE("path construction","[target]") {
  std::string fn = "zork.fq.gz";
  std::string path = "/this/is/a/test";
  Target targ(path,fn);
  TargetFriend tf(targ);
  REQUIRE(tf.getPath() == "/this/is/a/test/zork.fq.gz");
}
