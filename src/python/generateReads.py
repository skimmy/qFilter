#! /usr/bin/python

import argparse
import math
import random

import numpy as np
from scipy import stats
from Bio import SeqIO

import qualityUtil as qutil

outFileHandler = None
generateErrors = True

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("reference", help="fast file for reference sequence")
    parser.add_argument("distribution", help="distribution file for quality values")
    parser.add_argument("-M", "--number", help="number of generated reads", type=int, default=1000)
    parser.add_argument("-m", "--length", help="length of a single read", type=int, default=100)
    parser.add_argument("-o", "--output", help="fastq for the output")
    parser.add_argument("-E", "--noerror", help="if selected reads are generated with no error", action="store_true")
    return parser.parse_args()

def getRandomGenerator(freqs):
    s = sum(freqs)
    l = len(freqs)
    probs = [float(freqs[i])/float(s) for i in range(l)]
    quals = np.arange(l)
    dist = stats.rv_discrete(name='custm', values=(quals, probs))
    return dist

def loadDistribution(distFileName):
    distFile = open(distFileName)
    dist = []
    for line in distFile:
        dist.append(int(line))
    distFile.close()
    return dist

def loadReferenceSequence(referenceFileName):
    records = SeqIO.parse(referenceFileName, "fasta")
    return next(records).seq

def generateError(qualityValue, actualNucleotide):
    e = -1.0 * ( float(qualityValue) / 10.0 )
    p = math.pow(10.0, e)
    r = random.random()
    if r < p:
        nucs = ["A","C","G","T"]
        nucs.remove(actualNucleotide.upper())
        return nucs[random.randint(0,len(nucs)-1)]
    return actualNucleotide
    print(p)

def generateReads(refSeq, randGenQual, m, M, name="", errDist=None):
    reads = []
    N = len(refSeq)
    qualOffset = SeqIO.QualityIO.SANGER_SCORE_OFFSET 
    barN = N - m + 1
    for i in range(M):
        j = np.random.randint(barN)
        readSeq = str(refSeq)[j:j+m]
        readQual = ""
        readSeqNoErr = str(readSeq)
        temp = []
        readErrorProb = 1.0
        if generateErrors:
            for l in range(len(readSeq)):
                # here quality is generated and errors are introduced
                q = int(randGenQual.rvs())
                readErrorProb = readErrorProb * (1.0 - qutil.valueToProb(q)) # P = P * 10^(-Q/10) 
                readQual = readQual + SeqIO.QualityIO._phred_to_sanger_quality_str[q]
                temp.append(generateError(q,readSeq[l]))
        readErrorProb = 1.0 - readErrorProb
        readSeq = "".join(temp)       
        readHead = "@%s:%d pos=%d NoErr=%s Pe=%.15f" % (name, i, j, str(readSeqNoErr), readErrorProb)
        if outFileHandler != None:
            outFileHandler.write(readHead + "\n" + readSeq + "\n+\n" + readQual + "\n")
        else:
            reads.append((readSeq, readQual, readHead))
    return reads
 
if __name__ == "__main__":
    args = parseArguments()
    M = args.number
    m = args.length
    referenceFileName = args.reference
    distFileName = args.distribution
    outFileName = args.output
    if outFileName != None:
        outFileHandler = open(outFileName, "w")
    if args.noerror != None:
        generateErrors = False
    print "\nReference: %s\nDistribution: %s\n(M,m) = (%d, %d)\n" % (referenceFileName, distFileName,M,m)
    refSeq = loadReferenceSequence(referenceFileName)
    qDist = getRandomGenerator(loadDistribution(distFileName))
    reads = generateReads(refSeq, qDist, m, M, name="ecoli_sample")
    for r in reads:
        print(str(r[2]))
        print(str(r[0]))
        print(str(r[1]))
        print("")
    if outFileHandler != None:
        outFileHandler.close()
    
