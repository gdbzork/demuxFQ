//
// Created by Gord Brown on 2019-03-29.
//

#include <stdio.h>
#include "indexArgs.h"

int main(int argc,char **argv) {
  IndexArgs *args = new IndexArgs();
  args->process(argc,argv);
  if (!args->shouldExit()) {
  }
  return 0;
}
