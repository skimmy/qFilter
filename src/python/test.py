#! /usr/bin/python

if __name__ == "__main__":
    from Bio import SeqIO
    import sys
    if len(sys.argv) > 1:
        fastafile = sys.argv[1]
        filehandle = open(fastafile, "rU")
        records = SeqIO.parse(filehandle, "fastq")
    print (records.next().letter_annotations["phred_quality"])
