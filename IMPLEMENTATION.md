## demuxFQ: Implementation Notes

### Classes

* Destination -- a file to write Fastq to (includes details like filename,
  whether it is (should be) compressed, and the filehandle).
* Fastq -- a Fastq sequence
* FastqReader -- read Fastq sequentially (or statically in Fastq?)
* Index -- store an index, either from Fastq or a sample sheet
  * subclasses for single, dual indices
  * fast comparison for equality (override ==)
* IndexSet -- collect set of known indices
  * factory class for making new indices
  * implement a fast "seen" test
  * subclasses for set of sample sheet indices, FQ file indices
  * subclasses provide parsing for two cases
  * ensure duplicate index -> same object
* LineType -- static set of line types, code to determine line type.
* Log -- keep logs of results (if not )
* SampleSheet -- load, store, manipulate a sample sheet
* Util -- odds and ends
