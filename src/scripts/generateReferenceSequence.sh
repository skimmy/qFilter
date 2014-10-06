#!/bin/bash

# I/O variables
scriptDir="../python"
scriptName="generateSequence.py"
pythonInterpreter="python"
workingDir="/home/skimmy/filtering/data/exp"
outputFileName="reference.fasta"

# Sequence paramaters
N=10000
background=0 # 0: IID -- 1: GC-Rich -- 2: GC Poor 


# TODO: Parse arguments
while getopts "h" opt;
do
    case $opt in
	h)
	    ;;
    esac
done

# Process variables
outputFilePath="${workingDir}/${outputFileName}"

sequenceName="${outputFileName}_N${N}_BG${background}"

scriptPath="${scriptDir}/${scriptName}"
scriptArgs="-a ${sequenceName} -o ${outputFilePath} ${N}"

# Prepare working dir
mkdir -p $workingDir

# Invoke script
echo "$pythonInterpreter $scriptPath $scriptArgs"
$pythonInterpreter $scriptPath $scriptArgs