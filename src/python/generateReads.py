#! /usr/bin/python

import argparse

import numpy as np
from scipy import stats

from Bio import SeqIO

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("reference", help="fast file for reference sequence")
    parser.add_argument("distribution", help="distribution file for quality values")
    parser.add_argument("-M", "--number", help="number of generated reads", type=int, default=1000)
    parser.add_argument("-m", "--length", help="length of a single read", type=int, default=100)
    return parser.parse_args()

def getRandomGenerator(freqs):
    s = sum(freqs)
    l = len(freqs)
    probs = [float(freqs[i])/float(s) for i in range(l)]
    quals = np.arange(l)
    dist = stats.rv_discrete(name='custm', values=(quals, probs))
    # print(dist.rvs(size=10))
    # print probs

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

def generateReads(refSeq, randGenQual, m, M):
    reads = []
    N = len(refSeq)
    barN = N - m + 1
    for i in range(M):
        j = np.random.randint(barN)
        
        print(j)
        readSeq = str(refSeq)[j:j+m]
        readQual = ""
        reads.append((readSeq, readQual))
    return reads
    

if __name__ == "__main__":
    args = parseArguments()
    M = args.number
    m = args.length
    referenceFileName = args.reference
    distFileName = args.distribution
    print "\nReference: %s\nDistribution: %s\n(M,m) = (%d, %d)\n" % (referenceFileName, distFileName,M,m)
    refSeq = loadReferenceSequence(referenceFileName)
    qDist = loadDistribution(distFileName)
    getRandomGenerator(qDist)
    reads = generateReads(refSeq, qDist, m, M)
    for r in reads:
        print(str(r[0]))
    
