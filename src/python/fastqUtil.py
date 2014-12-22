#! /usr/bin/python

import argparse
import sys
import random

from Bio import SeqIO

tasksDict = {
    "truncate" : 1,
    "count" : 2,
    "sample" : 3
}

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("task", help="The operation to be performed")
    parser.add_argument("file", help="The fastq file used as input")
    parser.add_argument("-o", "--output", dest="out", help="The output fastq file", default="out.fastq")
    parser.add_argument("-M", "--reads-count", dest="M", help="Number of output reads", default=0)
    return parser.parse_args()    

def truncateFile(reads, M, outFile):
    """Truncates a set of reads with the first M reads. If the total number of reads is less than M, then all of them are dumped into the output file. The function always returns the actual number of reads written into the ouput"""
    ofh = open(outFile, "w")
    i = 0
    for read in reads:
        read = reads.next()
        ofh.write(read.format("fastq"))
        i += 1
        if (i >= M):
            break
    ofh.close()
    return i

def countReads(reads):
    count = 0
    for read in reads:
        reads
        count += 1
    return count

def sampleRead(reads, N, M, outFile):
    # To sample the file for a given M
    # generate M random numbers without
    # repetition use that to sample the set

    samples = sorted(random.sample(range(N), M))
    print(samples)
    ofh = open(outFile, "w")
    i = 0;
    j = 0;
    for read in reads:
        if (j >= M):
            break
        if i == samples[j]:
            j += 1
            ofh.write(read.format("fastq"))
        i += 1

    ofh.close()

        

if __name__ == "__main__":    
    args = parseArguments()
    task = args.task
    inFileName = args.file
    outFileName = args.out
    inFileHandler = open(inFileName, "rU")
    if (task in tasksDict) == False:
        print("[ERROR] - Unrecognized task: " + task)
        sys.exit(1)
    taskCode = tasksDict[task]
    if taskCode == 1:
        M = args.M
        print("Truncating...")
        truncateFile(SeqIO.parse(inFileHandler,"fastq"), M, outFileName)
    if taskCode == 2:
        print (countReads(SeqIO.parse(inFileHandler, "fastq")))
    if taskCode == 3:
        M = int(args.M)
        N = countReads(SeqIO.parse(open(inFileName, "rU"), "fastq"))
        sampleRead(SeqIO.parse(inFileHandler, "fastq"), N, M, outFileName)
    inFileHandler.close()

        
    
       
