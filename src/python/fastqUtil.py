#! /usr/bin/python

import argparse
import sys
import random

from Bio import SeqIO

checkNs = False

tasksDict = {
    "truncate" : 1,
    "count" : 2,
    "sample" : 3,
    "clean" : 4,
    "filter" : 5,
    "trim" : 6,
    "trimqual" : 7,
}

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("task", help="The operation to be performed")
    parser.add_argument("file", help="The fastq file used as input")
    parser.add_argument("-o", "--output", dest="out", help="The output fastq file", default="out.fastq")
    parser.add_argument("-M", "--reads-count", dest="M", help="Number of output reads", default=0)
    parser.add_argument("-q", "--min-quality", dest="q", help="Specifies minimum quality score acceptet", default=3)
    parser.add_argument("-m", "--read-length", dest="m", help="Length of considered read(s)", default=100)

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
        count += 1
    return count

def sampleRead(reads, N, M, outFile):
    # To sample the file for a given M
    # generate M random numbers without
    # repetition use that to sample the set

    samples = sorted(random.sample(range(N), M))
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

def cleanReads(reads, outFile):
    print("Cleaning fastq file {0}".format(inFileName))
    fh = open(outFile, "w")
    total = 0
    kept = 0
    for r in reads:
        total += 1
        if (str(r.seq).find('N') != -1):
            fh.write(r.format("fastq"))
            kept += 1
    fh.close()
    return (total, kept, total - kept)

def filterReads(reads, lengths, outFile):
    ofh = open(outFile, 'w')
    for r in reads:
        if (len(str(r.seq)) in lengths):
            ofh.write(r.format("fastq"))
    ofh.close()

# Trims at the beginning and at the end reads with quality <= qMin
def trimQualities(reads, qMin, outFile):
    ofh = open(outFile, "w")
    for read in reads:
        m = len(read)
        low = 0
        high = m-1
        quals = read.letter_annotations["phred_quality"]
        while (low < m and quals[low] <= qMin):
            low += 1
        while (high > 0 and quals[high] <= qMin):
            high -= 1
        if (low < high):
            ofh.write((read[low:high].format("fastq")))
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
    if taskCode == 4:
        (t,k,d) = cleanReads(SeqIO.parse(inFileHandler, "fastq"), outFileName)
        print("Kept {1} reads out of {0} (discaderd {2})".format(t,k,d))
    if taskCode == 5:
        m = int(args.m)
        filterReads(SeqIO.parse(inFileHandler, "fastq"), [m], outFileName)
    if taskCode == 7:
        q = int(args.q)
        trimQualities(SeqIO.parse(inFileHandler, "fastq"), q, outFileName)
        
    inFileHandler.close()

        
    
       
