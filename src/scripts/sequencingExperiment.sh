#! /bin/bash

# This script simulates an entire sequencing experiment. It starts from a given
# reference sequence (as a fast format) and several experiment parameters:
#     length of the sequence (required)
#     length of the read (default 50)
#     number of reads or coverage (default 10000 / 10)
#     quality distribution or sample fastq (default is uniform qualities [0,40])


