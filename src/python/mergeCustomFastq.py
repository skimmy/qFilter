#! /usr/bin/python

import argparse

from Bio import SeqIO

# dumps read into outFileHandler usinf form standard
def dump(read, outFileHandler, form="fastq"):
    outFileHandler.write(read.format(form))

# copies all remaining reads from records into outFileHandler using form standard
def dumpReads(records, outFileHandler, form = "fastq"):
    for read in records:
        outFileHandler.write(read.format(form))

# returns True proability error of read1 is greater then probability error for read2
def isReadProbabilityGreaterThen(read1, read2):
    # retrieve the two headers
    head1 = read1.description
    head2 = read2.description
    i1 = head1.find("Pe=")
    i2 = head2.find("Pe=")
    if (i1 == -1) or (i2 == -1):
        print("Error: No custom format reads")
        exit(1)
    p1 = float(head1[(i1+3):])
    p2 = float(head2[(i2+3):])
    return (p1 > p2)

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("file1", help="first file to merge")
    parser.add_argument("file2", help="second file to merge")
    parser.add_argument("outfile", help="output file")
    return parser.parse_args()

if __name__ == "__main__":
    # parse input arguments and open all files
    args = parseArguments()
    fileHandler1 = open(args.file1, "rU")
    fileHandler2 = open(args.file2, "rU")
    fileHandlerOut = open(args.outfile, "w")
    # Biopython fastq parsing
    reads1 = SeqIO.parse(fileHandler1, "fastq")
    reads2 = SeqIO.parse(fileHandler2, "fastq")    
    
    # start the scanning of the two input files

    # the idea is that we scan the whole file1 and if we end the cycling without
    # any exception, then file1 is all copied and file2 still may have records,
    # otherwise file2 is done and file may have more record to be dumped in the
    # output file
    file2EndReached = False
    print("Merging...")
    for read1 in reads1:
        greater = True
        try:
            while greater:
                read2 = reads2.next()
                if isReadProbabilityGreaterThen(read1, read2):
                    dump(read2, fileHandlerOut)
                else:
                    greater = False
        except StopIteration:
            file2EndReached = True
        dump(read1, fileHandlerOut)
        if file2EndReached:
            break
    
    if file2EndReached:
        print("Dumping file1...")
        dumpReads(reads1, fileHandlerOut)
    else:
        print("Dumping file2..")
        dumpReads(reads2, fileHandlerOut)

    # close all files and exit
    fileHandler1.close()
    fileHandler2.close()
    fileHandlerOut.close()
