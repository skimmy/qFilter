#!/usr/bin/python

import numpy as np


def noErrorBVector(m,k):
    """Generates 'b' vector for perfect match mapping (i.e. without mismatched)"""
    return np.ones(m-k+1, dtype=np.int)

def kmerCoverageScore(b, k):
    barm = len(b)
    m = barm + k - 1
    c = np.zeros(m, dtype=np.int)
    for i in range(barm):
        for j in range(k):
            c[i + j] += b[i]
    # for i in range(barm):
    #     j_low = max(0, i - k + 1)
    #     j_high = min(m, i + k - 1)
    #     c[i] = sum(b[j_low:(j_high + 1)])
    return c

def stationaryPoints(v):
    n = len(v)
    p = np.zeros(n)
    for i in range(n-1):
        p[i] = int(np.sign(v[i]) == np.sign(v[i+1]))
    return p

if __name__ == "__main__":    
    m = 16
    k = 4
    barm = m - k + 1
    b = noErrorBVector(m,k)
    x = np.ceil(barm/2)
    b[x-1] = 0
    b[x] = 0
    b[x+1] = 0
    b[x+2] = 0
    c = kmerCoverageScore(b,k)    
    d = np.gradient(c)
    p = stationaryPoints(d)
    print ("c = " + str(c))
    print ("p = " + str(np.array([int(x) for x in p])))
    print ("b = " + str(b))
    print ""
    print d
                   
    barm = m - k + 1
    
