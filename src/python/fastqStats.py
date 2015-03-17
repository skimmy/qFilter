#! /usr/bin/python

import argparse

from Bio import SeqIO

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("fastq", help="The file for which compute statistics")
    parser.add_argument("-M", "--reads-count", dest='M', help="Shows the number of reads", action='store_true')
    parser.add_argument("-m", "--average-read-length", dest='m', help="Shows the average length of reads", action='store_true')
    parser.add_argument("-d", "--lenght-distribution", dest='d', help="Calculates the distribution of lenghts of reads", action='store_true')
    parser.add_argument("-o", "--output", dest='o', help="Prefix for output files", default='output')
    return parser.parse_args()

def lengthsDictToArray(lDict, maxLength):
    lengthsList = [0] * maxLength
    for v in lDict:
        lengthsList[int(v) - 1] = int(lDict[v])
    return lengthsList
            

def processFastq(fastqFile):    
    inFile = open(fastqFile, "rU")
    reads = SeqIO.parse(inFile, "fastq")
    count = 0
    m = 0
    maxLength = 0
    lengthsDict = {}
    avg_read_length = 0.0
    for read in reads:
        count += 1
        m = len(str(read.seq))
        maxLength = max([m, maxLength])
        lengthsDict[m] = lengthsDict.get(m,0) + 1;
        avg_read_length += m 
    avg_read_length /= float(count)
    inFile.close()
    return (count, avg_read_length, lengthsDictToArray(lengthsDict, maxLength))

if __name__ == "__main__":
    args = parseArguments()
    inputFile = args.fastq
    outPrefix = args.o
    print("\n----------------------------------------------------------------------\n")
    print("Processing fastq file: " + str(inputFile))
    (M, m, d) = processFastq(inputFile)
    if args.M:
        print("Total reads (M): " + str(M))
    if args.m:
        print("Read Length (m): " + str(m))
    if args.d:
        outFilePath = outPrefix + "_length.dist"
        print("Read Length distribution (d) on file: " + outFilePath)
        fo = open(outFilePath, "w")
        fo.write( "\n".join(str(x) for x in d) )
        fo.close()
    print("\n----------------------------------------------------------------------\n")
