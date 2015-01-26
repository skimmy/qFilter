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
    p = float(qu.valueToProb(q))
    #    x = ( (1.0 - p)  / (math.log( (1.0 - p), 2)) )# + ( (p) / (math.log(p,2) + A) )
    x = float((1.0 - p) / float(math.log(1.0 - p,2)) + ( (p) / (math.log(p,2) + A) ))
    return x

if __name__ == "__main__":
    args = parseArguments()
    Q = range(1,30)
    pq = 1.0 / float(len(Q))
    H1 = 0.0
    H2 = 0.0
    tildeP = 0.0
    for q in Q:
        H1 = H1 + pq * alpha(q)
        tildeP = tildeP + pq * qu.valueToProb(q)    
        #print"%d  %f %f " % (q,qu.valueToProb(q),alpha(q))
    H2 = ( (1.0 - tildeP) / math.log(1.0 - tildeP) ) + ( tildeP / (math.log(tildeP,2) + A ) )
    print "%f %f" % (H1, H2)
    print pq
