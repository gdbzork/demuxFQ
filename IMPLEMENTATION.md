## demuxFQ: Implementation Notes

### Overview

The breakdown is roughly:

1. Index processing:
  * checking fastq headers, extracting indices
  * testing indices for matches (or near-matches)
  * calculating edit distances
  * keeping counts of observed indices
1. Sample sheet processing:
  * parsing, storing sample sheet
  * testing indices to see which destination they match
1. Fastq:
  * reading, storing fastq (possibly compressed source)
  * extracting indices, according to pattern
  * writing fastq to appropriate output streams (possibly compressed).
1. Command-line processing.
1. Utilities:
  * logging
  * determining the line-ending style of files

### Classes

The code is separated into a common directory with, you guessed it,
shared code, and specific directories for individual programs.  So
far there are only two programs:
* demuxFQ -- demultiplex fastq files, and
* indices -- examine and report on UMI and index sequences.

Common classes include:

| Class | Description | Status |
| ----- | ----------- | ------ |
| Destination | File to write demultiplexed results | pre |
| Fastq | A fastq sequence | pre |
| FastqReader | A reader and parser for fastq-formatted files | pre |
| Index | An index (fast match with threshold to other index)  | in progress |
| IndexSingle | A single index | in progress |
| IndexDual | A dual index | in progress |
| IndexPattern | A pattern to parse indices with | in progress |
| IndexSet | A set of indices | in progress |
| LineType | Utility to test line endings in a file | tested |
| Log | Utility to log messages (currently in util.cpp) | pre |
| SampleSheet | A sample sheet for demultiplexing | in progress |


IndexSet -- set of known indices (from fastq)
  * factory class for making new indices
  * implement a fast "seen" test
  * subclasses for set of sample sheet indices, FQ file indices
  * subclasses provide parsing for two cases
  * ensure duplicate index -> same object

### Implementation Considerations

1. If the sample sheet lists hundreds of indices, are we going to run into trouble with too many open file handles?
