//
// Created by brown22 on 3/29/19.
//

#include <boost/program_options.hpp>

#include <iostream>
#include "index.h"

boost::program_options::variables_map processOptions(int argc, char* argv[]) {
  boost::program_options::options_description opts("Options");
  boost::program_options::variables_map args;

  opts.add_options()
    ("bad,b", boost::program_options::value<std::string>(),"destination for non-matching indices")
    ("demux,d", "demultiplex input (as opposed to just summarizing)")
    ("extended,e", "look for extended metadata in sample sheet")
    ("force,f", "overwrite existing files")
    ("help,h", "display program help")
    ("outdir,o", boost::program_options::value<std::string>(), "destination directory for output files")
    ("pattern,p", boost::program_options::value<std::string>(), "patten to use for parsing indices")
    ("report,r", boost::program_options::value<double>(), "threshold to report unexpected indices")
    ("reverse,R", "reverse-complement second index")
    ("summary,s", boost::program_options::value<std::string>(), "write summary, to the named file")
    ("threshold,t", boost::program_options::value<int>(), "mismatch threshold (allow up to N mismatches)")
  ;

  boost::program_options::store(boost::program_options::parse_command_line(argc,argv,opts),args);
  boost::program_options::notify(args);

  if (args.count("help")) {
    std::cout << opts << "\n";
    return 0;
  }

  return args;
}

int main(int argc,char **argv) {
  boost::program_options::variables_map args = processOptions(argc,argv);

  std::cout << "alpha\n";
  return 0;
}
