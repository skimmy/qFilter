#!/bin/bash

# ------------------------------------------------------------------------------
#
# This script generates reads using sample file for computing quality value
# distribution. The following script are used and are supposed to be on the
# ../python/ directory
#
#   qualityValueStats.py         Compute the quality value distribution
#   generateReads.py             Generates a set of reads with given paramaters
#
# ------------------------------------------------------------------------------

clear

# SCRIPT PARAMETERS AND VARIABLES

# Start by setting all default values...
referenceFast="reference.fasta"
qualityDistFile="qaul.dist"
workingDir="~/filtering/data"
m=50
M=10000
q=50

# ...and then parse the command line parameters
while getopts "w:m:" opt;
do
    case $opt in
	# working directory option
	w)
	    workingDir=$OPTARG
	    ;;
	# m is the (fixed) length of the reads
	m)
	    m=$OPTARG
	    ;;
	# M is the number of generated reads
	M)
	    M=$OPTARG
	    ;;
	# q is the maximum quality value considered
	q)
	    q=$OPTARG
	    ;;
    esac
done


# step over the parsed arguments
shift $((OPTIND-1))

if [ "$#" -lt "2" ];
then
    echo -e "Error no required argument"
    exit
fi

referenceFast=$1
qualityDistFile=$2

# this are the required arguments

echo -e "******************* SCRIPT PARAMETERS *******************"
echo -e "- Reference fast file     ${referenceFast}"
echo -e "- Quality distribution    ${qualityDistFile}"
echo -e "- Working dirrectory      ${workingDir}"
echo -e "- Read Length             ${m}"  



# newline at the end of the whole script
echo -e ""

#cd ../python/
#python qualityValueStats.py ~/filtering/data/sample.fastq -q 40 -o ~/filtering/data/ecoli.sample.qdist
#python generateReads.py -M 100 -m 50 -o ~/filtering/data/ecoli.sample.custom.fastq ~/filtering/data/ecoli.fasta ~/filtering/data/ecoli.sample.qdist
