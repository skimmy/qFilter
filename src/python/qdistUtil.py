#!/usr/bin/python

import argparse
import sys

tasks  = {
    "nop " : -1,
    "average" : 0,
    "count" : 1,
    "all" : 100
}

def parseArguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("task", help="Task to be performed", default="nop")
    parser.add_argument("qdist", help="Input .qdist file")            
    # parser.add_argument("-o", "--optional", dest='o', help="Optional flag", action='store_true')
    # parser.add_argument("-d", "--default", help="SWith default", default="Hello")
    return parser.parse_args()

def loadQdist(filePath):
    fh = open(filePath, "rU")
    F = []
    for line in fh:
        F.append(float(line))
    fh.close()
    return F

def averageQuality(p):
    avg = 0
    for i in range(len(p)):
        avg = avg + i * p[i]
    return avg

if __name__ == "__main__":
    args = parseArguments()
    distFile = args.qdist
    taskNum = tasks[args.task.lower()]
    if taskNum < 0:
        print "Task " + str(taskNum)
        exit(0)
    freq = loadQdist(distFile)
    count = float(sum(freq))
    prob = [x /count for x in freq]
    if taskNum == 0 or taskNum == 100:
        print("Average: " + str(averageQuality(prob)))
    if taskNum == 1 or taskNum == 100:
        print("count:   " + str(int(count)))
