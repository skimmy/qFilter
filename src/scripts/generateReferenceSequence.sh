#!/bin/bash

# I/O variables
#scriptDir="../python"
scriptName="/home/skimmy/src/qFilter/src/python/generateSequence.py"
#pythonInterpreter="python"
workingDir="../data"
outputFileName="seq_iid.fasta"

# Sequence paramaters
N=10000
background=0 # 0: IID -- 1: GC-Rich -- 2: GC Poor 


# TODO: Parse arguments
while getopts "hn:" opt;
do
    case $opt in
	h)
	    ;;
	n)
	    N=$OPTARG
	    ;;
    esac
done

shift $((OPTIND-1))

# Process variables
outputFilePath="${workingDir}/${outputFileName}"

sequenceName="${outputFileName}_N${N}_BG${background}"

#scriptPath="${scriptDir}/${scriptName}"
scriptArgs="-a ${sequenceName} -o ${outputFilePath} ${N}"

# Prepare working dir
#mkdir -p $workingDir

# Invoke script
python $scriptName $scriptArgs