#! /usr/bin/python

import argparse

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("reference", help="fast file for reference sequence")
    parser.add_argument("distribution", help="distribution file for quality values")
    parser.add_argument("-n", "--number", help="number of generated reads", type=int, default=1000)
    parser.add_argument("-l", "--length", help="length of a single read", type=int, default=100)
    return parser.parse_args()

if __name__ == "__main__":
    parseArguments()
