## demuxFQ: Implementation Notes

### Classes

* Fastq -- a Fastq sequence
* FastqReader -- read Fastq sequentially (or statically in Fastq?)
* Index -- store an index, either from Fastq or a sample sheet
  * subclasses for single, dual indices
  * static char for delimiter
  * string describing index format
  * static parser
* IndexSet -- collect set of known indices
  * possibly implement a fast "seen" test
* LineType -- static set of line types, code to determine line type.
* Log -- keep logs of results (if not )
* SampleSheet -- load, store, manipulate a sample sheet
* Util -- odds and ends
