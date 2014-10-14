#!/usr/bin/python

import argparse

from Bio import SeqIO

import qualityUtil as qutil

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("fastq", help="The original 'fastq' reads file")
    parser.add_argument("output", help="Path of the output 'fastq' custom format file")
    return parser.parse_args()

if __name__ == "__main__":
    # parse command line arguments
    args = parseArguments()
    inputFile = args.fastq
    outputFile = args.output
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
        readHead = "@%s:%d pos=%d NoErr=%s Pe=%.15f" % (read.name, i, -1, "", float(1.0 - readProb))        
        read.id = readHead
        read.description = ""
        print(read.format("fastq"))
        outFileHandler.write(read.format("fastq"))
        i += 1
    # close files
    inFileHandler.close()
    outFileHandler.close()
