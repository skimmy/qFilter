#!/usr/bin/python

import argparse

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("input", help="Input file", default="File containing scores and errrors count")
    # parser.add_argument("opt", help="Required option")
    # parser.add_argument("-o", "--optional", dest='o', help="Optional flag", action='store_true')
    # parser.add_argument("-d", "--default", help="SWith default", default="Hello")
    return parser.parse_args()
    

if __name__ == "__main__":
    args = parseArguments()
    errors = []
    perfectMatch = []
    cumulative = []
    percentage = []
    fh = open(args.input, "r")
    for line in fh:
        err = int((line.split())[1])
        errors.append(err)
        tmp = 0
        if (err == 0):
            tmp = 1
        perfectMatch.append(tmp)
        cumulative.append(sum(perfectMatch))
        percentage.append( float(sum(perfectMatch)) / float(len(perfectMatch)) )
    x = range(len(percentage))
    x = range(len(percentage))
    import matplotlib.pyplot as plt
    plt.plot(x,percentage)
    plt.show()

    
