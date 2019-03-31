#define CATCH_CONFIG_MAIN

#include <string.h>
#include "catch.hpp"
#include "config.h"
#include "sampleSheet.h"

TEST_CASE("Sample Sheets","[SampleSheet]") {
//  std::string fn = sprintf("%s/%s",(char *)demux_BINARY_DIR,(char *)"test/testdata/sampleSheet_regular.txt");
  // std::string fnS (demux_BINARY_DIR), ("test/testdata/sampleSheet_regular.txt");
  char fn[100] = demux_BINARY_DIR;
  strcat(fn,"/test/testdata/sampleSheet_regular.txt");
  fprintf(stderr,"'%s'\n",fn);
  SampleSheet *s;
  Index::clearStaticData();
  s = SampleSheet::load(fn,true,false);
  REQUIRE(s != nullptr);
}

/*
    void testSingle(void) {
      char fn[100] = "@srcdir@/testdata/sampleSheet_oneLine.txt";
      SampleSheet *s;
      Index::clearStaticData();
      s = SampleSheet::load(fn,true,false);
      TS_ASSERT(s != NULL);
    }

    void testNoEoln(void) {
      char fn[100] = "@srcdir@/testdata/sampleSheet_noEoln.txt";
      SampleSheet *s;
      Index::clearStaticData();
      s = SampleSheet::load(fn,true,false);
      TS_ASSERT(s == NULL);
    }

    void testReverse(void) {
      char fn[100] = "@srcdir@/testdata/sampleSheet_regular.txt";
      SampleSheet *s;
      Index::clearStaticData();
      s = SampleSheet::load(fn,true,true);
      TS_ASSERT(s != NULL);
      Index* asrc = s->getIndex(0);
      Index* bsrc = s->getIndex(1);
      Index* atest = new Index("TAAGGCGA","GCGATCTA");
      Index* btest = new Index("TAAGGCGA","GCGGCCTT");
      TS_ASSERT(asrc->isMatch(*atest,0));
      TS_ASSERT(bsrc->isMatch(*btest,0));
    }
};
*/
