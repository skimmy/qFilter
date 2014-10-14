#! /usr/bin/python

import math

def valueToProb(q):
    return math.pow(10, -1.0 * float(q) / 10.0)

def valuesToProbIID(quals):
    p = 1.0
    for q in quals:
        p = p * (1.0 - valueToProb(q))
    return p


#def 

if __name__ == "__main__":
    for q in range(41):
        print(str(valueToProb(q)))
    quals = [33, 34, 34, 34, 34, 32, 34, 34, 33, 32, 24, 33, 34, 33, 32, 34, 33, 34, 16, 27, 31, 32, 32, 20, 33, 28, 32, 25, 26, 31, 21, 18, 26, 29, 26, 34]
    print("\n\n")
    print(valuesToProbIID(quals))

