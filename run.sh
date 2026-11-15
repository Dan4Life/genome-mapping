#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"
mkdir -p data results
ref=GCF_000005845.2_ASM584v2_genomic.fna.gz
reads=ERR022075_1.fastq.gz
for name in "$ref" "$reads"; do
    if [[ ! -e data/$name && -e ../$name ]]; then
        ln -s "../../$name" "data/$name"
    fi
done
[[ -e data/$ref ]] || curl -L "https://ftp.ncbi.nlm.nih.gov/genomes/all/GCF/000/005/845/GCF_000005845.2_ASM584v2/$ref" -o "data/$ref"
[[ -e data/$reads ]] || curl -L "https://ftp.sra.ebi.ac.uk/vol1/fastq/ERR022/ERR022075/$reads" -o "data/$reads"
g++ -O3 -std=c++17 map.cpp -o map
gzip -dc "data/$ref" > data/reference.fa
gzip -dc "data/$reads" | ./map > results/full.stats.tsv
