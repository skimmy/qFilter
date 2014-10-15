#! /usr/bin/python

import argparse

from Bio import SeqIO

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("fastq", help="The file for which compute statistics")
    parser.add_argument("-M", "--reads-count", dest='M', help="Shows the number of reads", action='store_true')
    parser.add_argument("-m", "--average-read-length", dest='m', help="Shows the average length of reads", action='store_true')
    return parser.parse_args()

def processFastq(fastqFile):
    inFile = open(fastqFile, "rU")
    reads = SeqIO.parse(inFile, "fastq")
    count = 0
    avg_read_length = 0.0
    for read in reads:
        count += 1
        avg_read_length += len(str(read.seq))
    avg_read_length /= float(count)
    inFile.close()
    return (count, avg_read_length)

if __name__ == "__main__":
    args = parseArguments()
    inputFile = args.fastq
    print("\n----------------------------------------------------------------------\n")
    print("Processing fastq file: " + str(inputFile))
    (M, m) = processFastq(inputFile)
    if args.M:
        print("Total reads (M): " + str(M))
    if args.m:
        print("Read Length (m): " + str(m))
    print("\n----------------------------------------------------------------------\n")
