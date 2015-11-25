#! /usr/bin/python


from Bio import SeqIO
import sys
import argparse
import math

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("input", help="input fastq file")
    parser.add_argument("-o", "--output", help="output file")
    parser.add_argument("-q", "--quality", help="maximum quality score considered (minimum is always 0)", type=int, default=50)
    parser.add_argument("-H", "--entropy", help="computes and print entropy of the quality distribution", action="store_true")
    args = parser.parse_args()
    return args

def frequencyToDistribution(freqs):
    dist = []
    N = float(sum(freqs))
    for f in freqs:
        dist.append(float(float(f) / N))
    return dist
        

def computeEntropy(d):
    H = 0.0
    for x in d:
        if x > 0:
            H += (float(x) * math.log(x,2)) 
    return -H

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
    # entropy comutation
    if args.entropy:
        qualDist = frequencyToDistribution(qualsVector)
        print "Entropy %f" %(computeEntropy(qualDist))

    outFileHandle = None
    if outFile != None:
        outFileHandle = open(outFile, "w")
    for q in qualsVector:
        if outFileHandle == None:
            print(q)
        else:
            outFileHandle.write(str(q) + "\n")
    fileHandle.close()
    if outFile != None:
        outFileHandle.close()
