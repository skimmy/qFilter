#! /bin/bash


# This script generates reads using sample file for computing quality value
# distribution.

cd ../python/
python qualityValueStats.py ~/filtering/data/sample.fastq -q 40 -o ~/filtering/data/ecoli.sample.qdist
python generateReads.py -M 100 -m 50 -o ~/filtering/data/ecoli.sample.custom.fastq ~/filtering/data/ecoli.fasta ~/filtering/data/ecoli.sample.qdist
