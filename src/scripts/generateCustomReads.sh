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

# PART 0 - SCRIPT INITIALIZATION

#clear

# SCRIPT PARAMETERS AND VARIABLES

# Start by setting all default values...
referenceFast="reference.fasta"
qualityDistFile="qaul.dist"
workingDir="~/filtering/data/exp"
m=50
M=10000
q=50
clearOnExit=0
scriptDir=../python

# ...and then parse the command line parameters
while getopts "w:m:M:ls:o:" opt;
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
	# set the output file
	o)
	    outputFile=$OPTARG
	    ;;
	# l when selected working dir is cleared and only reads file are kept
	l)
	    clearOnExit=1
	    ;;
	# s defines the dir for source scripts
	s)
	    scrptDir=$OPTARG
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

outputFile="${referenceFast%.*}.out.fastq"
echo -e "[DEBUG] ${outputFile}  ${referenceFast%.*}"


# this are the required arguments

echo -e "******************* SCRIPT PARAMETERS *******************"
echo -e "- Reference fast file     ${referenceFast}"
echo -e "- Quality distribution    ${qualityDistFile}"
echo -e "- Max quality value       ${q}"
echo -e "- Working dirrectory      ${workingDir}"
echo -e "- Read length             ${m}"
echo -e "- Generated reads         ${M}"
echo -e "- Output file             ${outputFile}"
echo -e "- Clear on Exit           ${clearOnExit}"
echo -e "- Script directory        ${scriptDir}"

# PART 1 - READ GENERATION

mkdir $workingDir
scriptCommand="${scriptDir}/generateReads.py"
scriptArgs="-m ${m} -M ${M} -o ${outputFile} ${referenceFast} ${qualityDistFile}"
python $scriptCommand $scriptArgs
echo "python $scriptCommand $scriptArgs"


# PART 2 - CLEARING DATA

# clear the working directory
if [ "$clearOnExit" == "1" ];
then
    echo -e "Clearing working dir"
    rm -rf $workingDir
fi

# newline at the end of the whole script
echo -e ""

#python qualityValueStats.py ~/filtering/data/sample.fastq -q 40 -o ~/filtering/data/ecoli.sample.qdist
#python generateReads.py -M 100 -m 50 -o ~/filtering/data/ecoli.sample.custom.fastq ~/filtering/data/ecoli.fasta ~/filtering/data/ecoli.sample.qdist
