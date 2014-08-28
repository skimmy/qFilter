#! /usr/bin/python


from Bio import SeqIO
import sys
import argparse

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("input", help="input fastq file")
    parser.add_argument("-o", "--output", help="output file")
    parser.add_argument("-q", "--quality", help="maximum quality score considered (minimum is always 0)", type=int, default=100)
    args = parser.parse_args()
    return args

if __name__ == "__main__":
    args = parseArguments()
    fileName =  args.input
    outFile =  args.output
    maxQuality = args.quality
    fileHandle = open(fileName, "rU")
    qualsVector = [0]*maxQuality
    for record in SeqIO.parse(fileHandle, "fastq"):
        temp = record.letter_annotations["phred_quality"]
        for x in temp:
            qualsVector[int(x)] += 1
    outFileHandle = None
    if outFile != None:
        outFileHandle = open(outFile, "w")
    for q in qualsVector:
        if outFileHandle == None:
            print(q)
        else:
            outFileHandle.write(str(q) + "\n")
