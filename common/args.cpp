#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <zlib.h>
#include <vector>
#include <fstream>
#include <errno.h>
#include <unistd.h>

Args::Args(void) {
  setDefaults();
}

void Args::doHelp() {
  int i;
  fprintf(stderr,"%s\n",usage);
  fprintf(stderr,"version: %s\n",VERSION);
  i = 0;
  fprintf(stderr,"options:\n");
  while (options[i] != NULL) {
    fprintf(stderr,"%s\n",options[i++]);
  }
}

void printParams(FILE *fd) {
  fprintf(fd,"# Configuration Parameters\n");
  fprintf(fd,"#   demultiplexing: %s\n",demux?"yes":"no");
  fprintf(fd,"#   summarizing: %s\n",summarize?"yes":"no");
  fprintf(fd,"#   save non-matching reads: %s\n",non_matching_fn==NULL?"no":non_matching_fn);
  fprintf(fd,"#   compressing: %s\n",compress?"yes":"no");
  fprintf(fd,"#   extended metadata: %s\n",extended_metadata?"yes":"no");
  fprintf(fd,"#   new-style headers: %s\n",new_style_headers?"yes":"no");
  fprintf(fd,"#   length first index: %d\n",len_first_index);
  fprintf(fd,"#   no gz suffix: %s\n",no_gz_suffix?"yes":"no");
  fprintf(fd,"#   output directory: %s\n",output_dir);
  fprintf(fd,"#   frequency to report: %f\n",report_threshold);
  fprintf(fd,"#   no sample sheet: %s\n",no_sample_sheet?"yes":"no");
  fprintf(fd,"#   threshold: %d\n",threshold);
  fprintf(fd,"#   reverse second: %s\n",reverse_second?"yes":"no");
  fprintf(fd,"#\n");
}

void setDefaults(void) {
  pars->non_matching_fn = NULL;
  pars->compress = false;
  pars->demux = false;
  pars->new_style_headers = false;
  pars->len_first_index = -1;
  pars->no_gz_suffix = false;
  pars->output_dir = (char *)".";
  pars->report_threshold = 0.001;
  pars->summarize = false;
  pars->summary_file = strdup("-");
  pars->no_sample_sheet = false;
  pars->threshold = 1;
  pars->extended_metadata = false;
  pars->reverse_second = false;
}

int processCmdLine(int argc,char **argv) {
  char c;
  while ((c = getopt(argc,argv,opts)) != -1) {
    switch (c) {
      case 'b': non_matching_fn = strdup(optarg); break;
      case 'c': compress = true; break;
      case 'd': demux = true; break;
      case 'e': extended_metadata = true; break;
      case 'h': doHelp(); exit(0);
      case 'i': new_style_headers = true; break;
      case 'l': len_first_index = atoi(optarg); break;
      case 'n': no_gz_suffix = true; break;
      case 'o': output_dir = strdup(optarg); break;
      case 'r': report_threshold = atof(optarg); break;
      case 'R': reverse_second = true; break;
      case 's': summarize = true; summary_file = strdup(optarg); break;
      case 'S': no_sample_sheet = true; break;
      case 't': threshold = atoi(optarg); break;
      case 'v': fprintf(stderr,"demuxFQ: version %s\n",VERSION);
                exit(0);
      default: doHelp(); exit(-1);
    }
  }
  return checkConsistency();
}

int checkConsistency(void) {
  if (!demux && !summarize) {
    fprintf(stderr,"Either '-d' (demultiplex) or '-s' (summarize) or both must be specified, or the program will not do anything useful.\n");
    doHelp();
    return -1;
  }
  if (no_sample_sheet && demux) {
    fprintf(stderr,"Sample sheet must be provided for demultiplexing.\n");
    doHelp();
    return -1;
  } else if (argc - ind == 0) { /* we don't have two parameters */
    doHelp();
    return -1;
  }
  return optind;
}

double perc(int n,int m) {
  double frac = ((int)(((double)n / (double)m) * 10000)) / 100.0;
  return frac;
}

void calculateDistances(Index *index,SampleSheet *ss,int **expected,int pos) {
  if (ss != NULL) {
    if (pos >= 0) {
      int d = ss->getIndex(pos)->hammingDistance(*index);
      expected[pos][d] += 1;
    }
  }
}

int splitFile(char **fns,int ind,int argc,SampleSheet *sheet,std::vector<Target *> targets,int rows,int compressed,int stringency,Target *badFile,int **expected,int *lost,bool summarize,bool demux) {
  gzFile fd;
  char buffer[LINELEN];
  char *rc;
  int index,i,count,bad;
  Index *indObj;

  count = 0;
  bad = 0;
  while (ind < argc) {
#ifdef DEBUG
    fprintf(stderr,"opening %s...\n",fns[ind]);
#endif
    fd = gzopen(fns[ind++],"r");
    if (fd == NULL) {
      fprintf(stderr,"failed to open '%s', errno=%d\n",fns[ind],errno);
      return -1;
    }
    rc = gzgets(fd,buffer,LINELEN);
    while (rc != NULL) {
      trimWhiteFromTail(buffer);
      indObj = Index::indexFromFastqHeader(buffer);
      if (indObj == NULL) { // probable corrupt fastq file
        gzclose(fd);
        return -1;
      }
      if (sheet != NULL) {
        index = sheet->check(*indObj,stringency);
        calculateDistances(indObj, sheet, expected, index);
        if (index >= 0) {
          if (demux) {
            strcat(buffer, "\n");
            targets[index]->write(buffer);
            for (i=0;i<3;i++) {
              gzgets(fd,buffer,LINELEN);
              targets[index]->write(buffer);
            }
          } else {
            for (i=0;i<3;i++) {
              gzgets(fd,buffer,LINELEN);
            }
          }
        } else {
          if (badFile != NULL) {
            strcat(buffer, "\n");
            badFile->write(buffer);
            for (i=0;i<3;i++) {
              gzgets(fd,buffer,LINELEN);
              badFile->write(buffer);
            }
          } else {
            for (i=0;i<3;i++) {
              gzgets(fd,buffer,LINELEN);
            }
          }
          bad++;
        }
      } else {
        for (i=0;i<3;i++) {
          gzgets(fd,buffer,LINELEN);
        }
      }
      rc = gzgets(fd,buffer,LINELEN);
      count++;
#ifdef DEBUG
      if (count % 100000 == 0) {
        fprintf(stderr,"%09d\r",count);
      }
#endif
    }
    gzclose(fd);
  }
  *lost += bad;
  if (demux && !summarize) {
    fprintf(stderr,"lost %d/%d reads (%.1f%%)\n",bad,count,perc(bad,count));
  }
  return count;
}

void dumpParams(struct params &pars,FILE *fd) {
  fprintf(fd,"# Configuration Parameters\n");
  fprintf(fd,"#   demultiplexing: %s\n",pars.demux?"yes":"no");
  fprintf(fd,"#   summarizing: %s\n",pars.summarize?"yes":"no");
  fprintf(fd,"#   save non-matching reads: %s\n",pars.non_matching_fn==NULL?"no":pars.non_matching_fn);
  fprintf(fd,"#   compressing: %s\n",pars.compress?"yes":"no");
  fprintf(fd,"#   extended metadata: %s\n",pars.extended_metadata?"yes":"no");
  fprintf(fd,"#   new-style headers: %s\n",pars.new_style_headers?"yes":"no");
  fprintf(fd,"#   length first index: %d\n",pars.len_first_index);
  fprintf(fd,"#   no gz suffix: %s\n",pars.no_gz_suffix?"yes":"no");
  fprintf(fd,"#   output directory: %s\n",pars.output_dir);
  fprintf(fd,"#   frequency to report: %f\n",pars.report_threshold);
  fprintf(fd,"#   no sample sheet: %s\n",pars.no_sample_sheet?"yes":"no");
  fprintf(fd,"#   threshold: %d\n",pars.threshold);
  fprintf(fd,"#   reverse second: %s\n",pars.reverse_second?"yes":"no");
  fprintf(fd,"#\n");
}

void summarizeFile(int total,int **expected,int lost,int threshold,SampleSheet *ss,double frequency,struct params &pars) {
  int i,j,wish,noConflict,t2;
  std::map<std::string,int>::iterator it;
  std::vector<Index *>unexpected;
  std::vector<Index *> *ilist;
  std::string snam;
  FILE *summaryFD;
  if (strcmp(pars.summary_file,"-") == 0) {
    summaryFD = stdout;
  } else {
    summaryFD = fopen(pars.summary_file,"w");
  }
  dumpParams(pars,summaryFD);
  fprintf(summaryFD,"%d reads\n",total);
  if (ss != NULL) {
    int ham;
    fprintf(summaryFD,"%d %.2f%% lost\n",lost,perc(lost,total));
    fprintf(summaryFD,"%d = threshold for match\n",threshold);
    ham = ss->minHammingDistance();
    fprintf(summaryFD,"%d = minimum distance between barcodes\n",ham);
    if (ss->isDual()) {
      t2 = threshold*2;
      noConflict = ham - t2;
    } else {
      t2 = threshold;
      noConflict = ham - threshold;
    }
    if (noConflict < 1) {
      fprintf(summaryFD,"WARNING: threshold allows for barcode clashes!\n");
    }
    fprintf(summaryFD,"Expected:\nIndex\tTotal\tBalance");
    for (i=0;i<=t2;i++) {
      fprintf(summaryFD,"\t\t%d",i);
    }
    wish = total / ss->rows();
    fprintf(summaryFD,"\n");
    for (i=0;i<ss->rows();i++) {
      int tot = 0;
      for (j=0;j<=t2;j++) {
        tot += expected[i][j];
      }
      fprintf(summaryFD,"%s\t%d\t%.2f%%",ss->getIndex(i)->repr().c_str(),tot,perc(tot,wish));
      for (j=0;j<=t2;j++) {
        fprintf(summaryFD,"\t%d\t%.2f%%",expected[i][j],perc(expected[i][j],total));
      }
      snam = ss->getIndex(i)->getName();
      if (snam != "") {
        fprintf(summaryFD,"\t%s",snam.c_str());
      }
      fprintf(summaryFD,"\n");
    }
    ilist = ss->getIndices();
  } else {
    ilist = NULL;
  }
  Index::dumpIndices(ilist,unexpected,frequency,summaryFD);
  if (ss != NULL) {
    fprintf(summaryFD,"Unexpected Indices:\n");
    if (unexpected.size() > 0) {
      std::vector<Index *>::iterator it;
      for (it=unexpected.begin(); it!=unexpected.end(); it++) {
        fprintf(summaryFD,"%9d\t%s\n",Index::getCount(*it),(*it)->repr().c_str());
      }
    } else {
      fprintf(summaryFD,"none\n");
    }
  }
}


int main(int argc,char **argv) {
  int rowCount,i,j,ind;
  char *sampleSheetFN;
  std::vector<Target *> targets;
  SampleSheet *sheet;
  struct params pars;
  Target *badTarget = NULL;
  int **expected;
  int total,lost=0;
  int t2;

  ind = readOptions(argc,argv,&pars);

  Index::setParams(pars.new_style_headers,pars.len_first_index);
  if (pars.no_sample_sheet) {
    sampleSheetFN = NULL;
//    fastqFN = argv[ind];
    sheet = NULL;
  } else {
    sampleSheetFN = argv[ind];
//    fastqFN = argv[ind+1];
    ind++;
    sheet = SampleSheet::load(sampleSheetFN,pars.extended_metadata,pars.reverse_second);
    if (sheet == NULL) {
      fprintf(stderr,"ERROR: missing, empty or incorrect sample sheet file '%s'.  Exiting.\n",sampleSheetFN);
      return -1;
    }
    rowCount = sheet->rows();
    if (sheet->isDual()) {
      t2 = pars.threshold*2;
    } else {
      t2 = pars.threshold;
    }
    expected = new int*[sheet->rows()];
    for (i=0;i<sheet->rows();i++) {
      expected[i] = new int[t2+1];
      for (j=0;j<=t2+1;j++) {
        expected[i][j] = 0;
      }
    }
  }

  if (pars.non_matching_fn != NULL) {
    badTarget = new Target(pars.non_matching_fn,pars.output_dir,pars.compress,pars.no_gz_suffix);
    badTarget->open();
  }

  if (pars.demux) {
    for (i=0;i<rowCount;i++) {
      Target *t = new Target(sheet->getFN(i),pars.output_dir,pars.compress,pars.no_gz_suffix);
      targets.push_back(t);
      t->open();
    }
  }
  int rv = 0;
  Index::zeroCounts();
  total = splitFile(argv,ind,argc,sheet,targets,rowCount,pars.compress,pars.threshold,badTarget,expected,&lost,pars.summarize,pars.demux);
  switch (total) {
    case -1: rv = -1;
             break; /* readFile displayed an error */
    case 0:  fprintf(stderr,"%s: empty file\n",argv[i]);
             rv = -2;
             break;
    default: if (pars.summarize) {
               summarizeFile(total,expected,lost,pars.threshold,sheet,pars.report_threshold,pars);
             }
             break;
  }
  if (pars.demux) {
    for (i=0;i<rowCount;i++) {
      delete targets[i];
    }
    if (badTarget != NULL) {
      delete badTarget;
    }
  }
  return rv;
}
