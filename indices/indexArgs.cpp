#include <iostream>
#include <string.h>
#include <unistd.h>
#include "indexArgs.h"
#include "config.h"

const char *IndexArgs::opts = "d:f:hv";
const char *IndexArgs::defaultFmt = "11111111UUUUUUUUU+22222222";

IndexArgs::IndexArgs(void) {
  formatStr = strdup(defaultFmt);
  return;
}

void IndexArgs::doHelp(void) {
  std::cerr << "This is the help." << std::endl;
}

void IndexArgs::doVersion(void) {
  std::cerr << "version " << demux_VERSION_MAJOR << "." << demux_VERSION_MINOR << std::endl;
}

bool IndexArgs::process(int argc,char **argv) {
  char c;
  bool okay = true;
  while ((c = getopt(argc,argv,this->opts)) != -1) {
    switch (c) {
      case 'd': delimiter = *optarg; break;
      case 'f': formatStr = strdup(optarg); break;
      case 'h': doHelp(); help = true; break;
      case 'v': doVersion(); version = true; break;
      default: doHelp(); okay = false;
    }
  }
  return okay;
}
