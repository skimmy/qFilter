#! /usr/bin/python

import math

def valueToProb(q):
    return math.pow(10, -1.0 * float(q) / 10.0)

def valuesToProbIID(quals):
    p = 1.0
    for q in quals:
        p = p * valueToProb(q)
    return p

def valuesToErrorProbIID(quals):
    p = 1.0
    for q in quals:
        p = p * (1.0 - valueToProb(q))
    return p


#def 

if __name__ == "__main__":
    for q in range(41):
        print(str(valueToProb(q)))
    quals = [30, 30, 22, 21, 27, 23]
    print("\n\n")
    print(valuesToProbIID(quals))
    print(valuesToErrorProbIID(quals))

