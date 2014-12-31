#! /bin/bash

# PART 0 - SCRIPT INITIALIZATION

# Scripts and applications to run
generatorScript=../scripts/generateCustomReads.sh
sorterExec=../c/reader.out

# I/O parameters
workingDir=~/filtering/data/exp
outputFastq=${workingDir}/out.fastq

# Read arguments
referenceequence=$1
M=$2
m=$3
qualityDistribution=$4

# Sorting reads
fraction=$4

# PART 1 - GENERATE READS USING CUSTOM FORMAT
bash ${generatorScript} -m ${m} -M ${M} -w ${workingDir} -o ${outputFastqName} ${referenceSequence} ${qaulityDistribution}

# PART 2 - SORT THE READS
${sorterExec} -f ${fraction} ${outputFastq} 
