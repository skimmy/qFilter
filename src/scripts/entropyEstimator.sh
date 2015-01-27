#!/bin/bash

fastqFile=$1
qdistFile="${fastqFile}.qdist"

echo -e ""
echo -e "--------------- PARAMETERS ---------------"
echo -e "Fastq:          ${fastqFile}"
echo -e "Qaulit Dist:    ${qdistFile}"
echo -e "------------------------------------------"
echo -e ""

echo -e "[QUTIL] - Calculating qdist..."
python ../python/qualityValueStats.py -o ${qdistFile} -q 50 ${fastqFile}

echo -e "[ENTROPY] - Calculating entropies..."
python ../python/entropyCalculator.py ${qdistFile}