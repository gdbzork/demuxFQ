#ifndef ARGS_H
#define ARGS_H

#include <stdio.h>

class Args {

  public:
    Args(void);
    int processCmdLine(int argc,char **argv);
    void printParams(FILE *fd);
    void doHelp();

    char *nonMatchingFn(void) { return non_matching_fn;};
    bool compressOutput(void) { return compress;};
    bool wantDemux(void) { return demux;};
    bool haveExtendedMetadata(void) { return extended_metadata;};
    bool newStyleHeaders(void) { return new_style_headers;};
    int lenFirstIndex(void) { return len_first_index;};
    bool noGzSuffix(void) { return no_gz_suffix;};
    char *outputDir(void) { return output_dir;};
    float reportingThreshold(void) { return report_threshold;};
    bool wantSummary(void) { return summarize;};
    bool haveSampleSheet(void) { return !no_sample_sheet;};
    int mismatchMax(void) { return threshold;};
    char *summaryFile(void) { return summaryFile;};
    bool reverseSecondIndex(void) { return reverse_second;};
    char *sampleSheet(void) { return sample_sheet;};
    char[] fastqFiles(void) { return fastq_list;};

  protected:
    void setDefaults(void);
    int checkConsistency(void);

  private:
    static char usage[] = "usage: demuxIllumina [-b Filename] [-c] [-d] [-e] [-h] [-i] [-l N] [-n] [-o outputDir] [-R] [-r nn] [-S] [-s fn] [-t threshold] [-v] [sampleSheet.txt] data.fq";
    static char *options[] = {
      (char *)"  -b Filename: save non-matching barcodes to file 'Filename'",
      (char *)"  -c: compress output files via gzip, append .gz suffix if not present in filenames (default uncompressed)",
      (char *)"  -d: demultiplex the file(s)",
      (char *)"  -e: sample sheet includes 'e'xplanations, i.e. sample names",
      (char *)"  -h: display help text",
      (char *)"  -i: assume new-style Illumina fastq headers",
      (char *)"  -l N: length of 1st index in fastq, if longer than in sample sheet",
      (char *)"  -n: do not append a .gz suffix to compressed output",
      (char *)"  -o Dir: write output files to directory 'Dir'",
      (char *)"  -R: reverse complement second index in sample sheet, if dual indexes present (for 4000, NextSeq)",
      (char *)"  -r <nn>: report reads with frequency at least 'nn' (default 0.001)",
      (char *)"  -S: summarise without sample sheet (required if sample sheet not present)",
      (char *)"  -s FN: write summary to FN ('-' indicates stdout) (will overwrite existing file)",
      (char *)"  -t N: allow up to N mismatches per index (default 1)",
      (char *)"  -v: report version of software and exit",
      NULL
    };
    static char opts[] = "b:cdehil:no:Rr:Ss:t:v";

    char *non_matching_fn;
    bool compress;
    bool demux;
    bool extended_metadata;
    bool new_style_headers;
    int len_first_index;
    bool no_gz_suffix;
    char *output_dir;
    float report_threshold;
    bool summarize;
    bool no_sample_sheet;
    int threshold;
    char *summary_file;
    bool reverse_second;
    char *sampleSheet;
    Vector<char *> fastq_list;
};
