#! /usr/bin/python

def printUsage():
    print """Usage:
   qualityValueStats <fastq_file>
"""

from Bio import SeqIO
import sys

if __name__ == "__main__":
    if len(sys.argv) < 2:
        printUsage()
        sys.exit(1)
    fileName = sys.argv[1]
    fileHandle = open(fileName, "rU")
    qualsVector = [0]*100
    for record in SeqIO.parse(fileHandle, "fastq"):
        temp = record.letter_annotations["phred_quality"]
        for x in temp:
            qualsVector[int(x)] += 1
    for q in qualsVector:
        print(q)
    
