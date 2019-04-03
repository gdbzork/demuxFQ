#include <string.h>
#include "catch.hpp"
#include "config.h"
#include "sampleSheet.h"

TEST_CASE("Sample Sheets","[SampleSheet]") {
  char fn[100] = demux_BINARY_DIR;
  strcat(fn,"/test/testdata/sampleSheet_regular.txt");
  fprintf(stderr,"'%s'\n",fn);
  SampleSheet *s;
  Index::clearStaticData();
  s = SampleSheet::load(fn,true,false);
  REQUIRE(s != nullptr);
}

TEST_CASE("Single Index","[SampleSheet]") {
  char fn[100] = demux_BINARY_DIR;
  strcat(fn,"/test/testdata/sampleSheet_oneLine.txt");
  SampleSheet *s;
  Index::clearStaticData();
  s = SampleSheet::load(fn,true,false);
  REQUIRE(s != nullptr);
}

TEST_CASE("No Eoln","[SampleSheet]") {
  char fn[100] = demux_BINARY_DIR;
  strcat(fn,"/test/testdata/sampleSheet_noEoln.txt");
  SampleSheet *s;
  Index::clearStaticData();
  s = SampleSheet::load(fn,true,false);
  REQUIRE(s == nullptr);
}

TEST_CASE("Reverse","[SampleSheet]") {
  char fn[100] = demux_BINARY_DIR;
  strcat(fn,"/test/testdata/sampleSheet_regular.txt");
  SampleSheet *s;
  Index::clearStaticData();
  s = SampleSheet::load(fn,true,true);
  REQUIRE(s != nullptr);
  Index* asrc = s->getIndex(0);
  Index* bsrc = s->getIndex(1);
  Index* atest = new Index("TAAGGCGA","GCGATCTA");
  Index* btest = new Index("TAAGGCGA","GCGGCCTT");
  REQUIRE(asrc->isMatch(*atest,0));
  REQUIRE(bsrc->isMatch(*btest,0));
}
