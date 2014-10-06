#! /bin/bash

# This script simulates an entire sequencing experiment. It starts from a given
# reference sequence (as a fast format) and several experiment parameters:
#     length of the sequence (required)
#     length of the read (default 50)
#     number of reads or coverage (default 10000 / 10)
#     quality distribution or sample fastq (default is uniform qualities [0,40])

# PART 0 - SCRIPT PREPARATION

# Variables (with default values)
workingDir=~/filtering/data/exp
sequenceFileName="reference.fasta"
readsFileName="reference.out.fastq"
sortedReadsFileName="reference.out.fastq.out"
qualityDistFilePath=~/filtering/data/sample.qdist

readSorter=read_sorter
aligner=alignSW

# TODO: Parse arguments
while getopts "h" opt;
do
    case $opt in
	h)
	    ;;
    esac
done

# PART 1 - SEQUENCE AND READS GENERATION

# compute values after options parsing
sequenceFilePath="${workingDir}/${sequenceFileName}"
readsFilePath="${workingDir}/${readsFileName}"
sortedReadsFilePath="${workingDir}/${sortedReadsFileName}"

# create the sequence
echo "- GENERATING SEQUENCE..."
echo "bash generateReferenceSequence.sh -o ${sequenceFilePath}"
bash generateReferenceSequence.sh -o ${sequenceFilePath}
echo ""

# generate the reads
echo "- GENERATING READS"
echo "bash generateCustomReads.sh ${sequenceFilePath} ${qualityDistFilePath}"
#bash generateCustomReads.sh ${sequenceFilePath} ${qualityDistFilePath}
echo ""

# PART 2 - READS SORTING
echo "- READ SORTING"
echo "${readSorter} -X ${readsFilePath}"
$readSorter ${readsFilePath}
echo ""

# sort reads

# PART 3 - ALIGNMENT
echo "- ALIGNING READS"
echo "$aligner -g ${sequenceFilePath} -r ${sortedReadsFilePath}"
$aligner -g ${sequenceFilePath} -r ${sortedReadsFilePath}
echo ""

# PART 4 - POST PROCESSING
