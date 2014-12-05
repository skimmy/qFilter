#!/usr/bin/python

import argparse
import re

from Bio import SeqIO

import qualityUtil as qutil

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("fastq", help="The original 'fastq' reads file")
    parser.add_argument("output", help="Path of the output 'fastq' custom format file")
    parser.add_argument("-Z", "--min-info", dest="mininfo", help="If set only prints sequence and qualities", action="store_true")
    parser.add_argument("-z", "--seq-only", dest="seqonly", help="If set only prints sequence", action="store_true")
    return parser.parse_args()

def minimalInformation(inFile, outFile, quals=True):
    fin = open(inFile, "r")
    fout = open(outFile, "w")
    i = 0
    for line in fin:
        if (i % 4) == 1:
            fout.write(line)
        if (((i % 4) == 3) and (quals)):
            fout.write(line)
        i += 1
        
    fin.close()
    fout.close()

if __name__ == "__main__":
    # parse command line arguments
    args = parseArguments()
    inputFile = args.fastq
    outputFile = args.output
    # prints only sequence and qualities
    if (args.mininfo == True):
        minimalInformation(inputFile, outputFile)
        exit(0)
    if (args.seqonly == True):
        minimalInformation(inputFile, outputFile, quals=False)
        exit(0)
    
    # open out files
    inFileHandler = open(inputFile, "rU")
    # WARNING: file will be overwrite 
    outFileHandler = open(outputFile, "w")
    i = 0
#    SeqIO.QualityIO.SANGER_SCORE_OFFSET
    for read in SeqIO.parse(inFileHandler, "fastq"):
        qualities = read.letter_annotations["phred_quality"]
        readProb = qutil.valuesToProbIID(qualities)
        # we may try to derive name and id from read.name
        readName = (re.split("\.|:|,|\|", read.id))[0]        
        readHead = "%s:%d pos=%d NoErr=%s Pe=%.15f" % (readName[0:4], i, 0, str(read.seq), float(1.0 - readProb))        
        read.id = readHead
        read.description = ""        

        outFileHandler.write(read.format("fastq"))
        i += 1
    # close files
    inFileHandler.close()
    outFileHandler.close()
