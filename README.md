# E. coli read mapping

C++17 implementation and [short report](REPORT.md) for the mapping assignment.

Requires `g++`, `gzip` and `curl` on Linux/WSL.

```bash
bash run.sh
```

This downloads the data (or reuses files in `data/` or the parent folder), compiles the mapper, and writes `results/full.stats.tsv`.

To run with existing uncompressed files, put the reference in `data/reference.fa`, then:

```bash
g++ -O3 -std=c++17 map.cpp -o map
./map < reads.fastq > results/full.stats.tsv
```

The code assumes one reference sequence and valid four-line FASTQ records with 100-base uppercase reads. It uses 12-base seeds and allows five substitutions.
