#!/usr/bin/python

import argparse

from Bio import SeqIO

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("reference", help="fast file for the reference sequence")
    parser.add_argument("reads", help="fasta or fastq file for the reads")
    return parser.parse_args()

def printArguments(args):
    print("Reference file    " + args.reference)
    print("Reads file        " + args.reads)

def hammingDistance(s1, s2):
    count = 0
    for i in range(len(s1)):
        if s1[i] == s2[i]:
            count += 1
    return count

if __name__ == "__main__":
    # parse input argumnets
    args = parseArguments()
    printArguments(args)
    referenceFile = args.reference
    readsFile = args.reads
    # prepare variables
    records = []
    # loads reference sequence
    referenceSeq = str((SeqIO.parse(referenceFile, "fasta")).next().seq)       
    # scan reads and compute their distance
    for read in SeqIO.parse(readsFile, "fasta"):
        readSeq = str(read.seq)        
        m = len(readSeq)
        header = read.description

        # find the sequencing position
        begin = header.find('pos=') + 4
        end = header.find(' ', begin)
        seqPos = (int(header[begin:end]))

        # find read id        
        readId = header[0:header.find(' ',0)]

        # compute the hamming distance and insert it the output list
        distance = (hammingDistance(readSeq, referenceSeq[seqPos:seqPos+m]))
        print "(%s, %d)" %(readId, distance)
        records.append((readId, distance))

    
