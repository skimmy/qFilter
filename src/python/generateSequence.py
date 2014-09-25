#! /usr/bin/python

import argparse

from Bio import SeqIO
from Bio.Seq import Seq
from Bio.SeqRecord import SeqRecord

from scipy import stats

pHigh = 1.0 / 3.0
pLow = 1.0 / 6.0

def parseArguments():
    parser  = argparse.ArgumentParser()
    parser.add_argument("length", help="length of the generated sequence", type=int)
    parser.add_argument("-a", "--name", help="name of the reference sequence", default="seq_")
    parser.add_argument("-o", "--output", help="output file path (stdout if None or empy)", default=None)
    return parser.parse_args()

def generateIidSequence(N):
    probs = [0.25]*4
    return generateSequenceWithProbabilityVector(N, probs)

def generateGCRichSequence(N):
    probs = [pLow, pHigh, pHigh, pLow]
    return generateSequenceWithProbabilityVector(N, probs)

def generateSequenceWithProbabilityVector(N, probs):
    indices = [0, 1, 2, 3]
    symbols = ["A","C", "G", "T"]
    dist = stats.rv_discrete(name='custm', values=(indices, probs))
    sequence = []
    for i in range(N):
        sequence.append(symbols[dist.rvs()])
    return "".join(sequence)

if __name__ == "__main__":    
    args = parseArguments()
    n = args.length
    name = args.name
    output = args.output
    header = (">%s %d" % (name, n))
    sequence = generateIidSequence(n)
    # create the SeqRecord object for biopython
    description= ("%d" % n)
    record = SeqRecord(Seq(sequence), id=name, name=name, description=description)
    if output != None and output != "":
        # output option set use BioPython to write a fasta file
        f = open(output, "w")
        SeqIO.write([record], f, "fasta")
        f.close()
    else:
        print ("%s\n%s" % (header, sequence))    
