# Mapping E. coli reads

I mapped all reads in `ERR022075_1.fastq.gz` to the E. coli K-12 MG1655 reference (NC_000913.3), which has 4,641,652 bases. Each read is 100 bases long. Only the supplied first-mate file was used, so reads were mapped independently.

The C++ mapper uses a direct-address index of 12-base seeds, seed-and-extend search on both strands, and Hamming distance to allow up to five substitutions. It searches six disjoint seeds: with at most five mismatches, at least one seed must match exactly. A difference array and prefix sums calculate coverage.

| Measure | Result |
| --- | ---: |
| Reads processed | 22,720,100 |
| Reads mapped | 22,246,063 (97.91%) |
| Unique best placement, out of all reads | 96.09% |
| Multiple best placements, out of all reads | 1.82% |
| Aligned-base identity | 99.79% |
| Genome covered at least once | 99.04% |
| Mean depth over the whole genome | 479.27x |

Unique means exactly one best `(start, strand)` placement; multi-mapped means several placements tie for the fewest mismatches. Worse placements do not count. Alignment identity is the percentage of aligned bases matching the reference.

Coverage uses one best placement per mapped read. Ties prefer the forward strand, then the lowest position on that strand, so ambiguous reads can bias local depth.

The mapper handles substitutions only. It does not allow indels, clipping, or alignments across the circular genome origin. `N` counts as a mismatch, and base qualities do not affect alignment scores.

Data: [reference FASTA](https://ftp.ncbi.nlm.nih.gov/genomes/all/GCF/000/005/845/GCF_000005845.2_ASM584v2/GCF_000005845.2_ASM584v2_genomic.fna.gz), [reads](https://ftp.sra.ebi.ac.uk/vol1/fastq/ERR022/ERR022075/ERR022075_1.fastq.gz).
