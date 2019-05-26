## demuxFQ: Implementation Notes

### Classes

The code is separated into a common directory with, you guessed it,
shared code, and specific directories for individual programs.  So
far there are only two programs:
* demuxFQ -- demultiplex Fastq files, and
* indices -- examine and report on UMI and index sequences.

Common classes include:

| Class | Description | Status |
| ----- | ----------- | ------ |
| Fastq | A Fastq sequence | pre |
| FastqReader | A reader and parser for Fastq-formatted files | pre |
| Index | An index (fast match with threshold to other index)  | in progress |
| IndexSingle | A single index | in progress |
| IndexDual | A dual index | in progress |
| IndexPattern | A pattern to parse indices with | in progress |
| IndexSet | A set of indices | in progress |
| LineType | Utility to test line endings in a file | tested |
| Log | Utility to log messages (currently in util.cpp) | pre |
| SampleSheet | A sample sheet for demultiplexing | in progress |


IndexSet -- set of known indices (from Fastq)
  * factory class for making new indices
  * implement a fast "seen" test
  * subclasses for set of sample sheet indices, FQ file indices
  * subclasses provide parsing for two cases
  * ensure duplicate index -> same object
