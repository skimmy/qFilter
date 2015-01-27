#!/usr/bin/python

import argparse
import math

import qualityUtil as qu

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("distribution", help="Quality distribution .qdist")
    # parser.add_argument("-o", "--optional", dest='o', help="Optional flag", action='store_true')
    # parser.add_argument("-d", "--default", help="SWith default", default="Hello")
    return parser.parse_args()

A = float(math.log(3,2))

def alpha(q):
    if q == 0:
        return 0
    p = float(qu.valueToProb(q))
    q = float(1.0 - p)
    x = A - p * math.log(p,2) - q * math.log(q,2)
    return x

def loadQualityDistribution(distFile):
    fh = open(distFile, "rU")
    Q = []
    for line in fh:
        Q.append(float(line))
    tot = sum(Q)
    F = [x / float(tot) for x in Q]         
    return F

if __name__ == "__main__":
    args = parseArguments()
    distFile = args.distribution
    Q = loadQualityDistribution(distFile)
    pq = 1.0 / float(len(Q))
    H1 = 0.0
    H2 = 0.0
    tildeP = 0.0
    for q in Q:
        H1 = H1 + pq * alpha(q)
        tildeP = tildeP + pq * qu.valueToProb(q)    
        #print"%d  %f %f " % (q,qu.valueToProb(q),alpha(q))
    tildeQ = 1.0 - tildeP
    H2 = A - tildeP * math.log(tildeP,2) - tildeQ * math.log(tildeQ, 2)
    print "%f %f %f" % (H1, H2, math.fabs(H1 - H2))

