#! /usr/bin/python

import argparse

def parseArguments():
    parser  = argparse.ArgumentParser()
    return parser.parse_args()

if __name__ == "__main__":
    args = parseArguments()
