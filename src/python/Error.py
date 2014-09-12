#! /usr/bin/python

import numpy as np
from scipy import stats

class ErrorGenerator(object):

    # ------------------------------------------------------ #
    #                  CONSTANTS DEFINITION                  #
    # ------------------------------------------------------ #
    
    # correspondance between integers and bases
    basesListString = ["A", "C", "G", "T"]
    basesDictNumber = { "A" : 0, "C" : 1, "G" : 2, "T" : 3, "a" : 0, "c" : 1, "g" : 2, "t" : 3 }

    # correspondance between integers and error types
    errorTypeListString = ["C", "S", "I", "D"] 
    errorTypeDictNumber = {"C" : 0, "S" : 1, "I" : 2, "D" : 3}
    
    
    # ------------------------------------------------------ #
    #                 DISTRIBUTIONS VARIABLE                 #
    # ------------------------------------------------------ #

    # defualt quality distribution is uniform in [0,50)
    defaultQualDist = [0.02]*50
    # defualt error distribution is uniform on all possible errors
    defaultErrTypeDist = [0.25]*5
    # defualt substitution matrix is uniform ALL FOUR bases
    defaultSubMatrixDist = {
        "A" : { "A" : 0.25, "C" : 0.25, "G" : 0.25 , "T" : 0.25 },
        "C" : { "A" : 0.25, "C" : 0.25, "G" : 0.25 , "T" : 0.25 },
        "G" : { "A" : 0.25, "C" : 0.25, "G" : 0.25 , "T" : 0.25 },
        "T" : { "A" : 0.25, "C" : 0.25, "G" : 0.25 , "T" : 0.25 }
    }

    # actual distributions
    qualDist = None
    errTypeDist = None
    subMatrixDist = None

    # ------------------------------------------------------ #
    #           DISTRIBUTION GENERATORS FROM SciPy           #
    # ------------------------------------------------------ #
    qualGen = None
    errTypeGen = None
    substGen = None    

    def __init__(self, qDist=None):
        self.qualDist = self.defaultQualDist
        self.errTypeDist = self.defaultErrTypeDist
        self.subMatrixDist = self.defaultSubMatrixDist
        self.initQualityDistribution(qDist)
        
    def initQualityDistribution(self, qDist=None):
        if (qDist != None):
            self.qualDist = qDist
        x = np.arange(len(self.qualDist))
        self.qualGen = stats.rv_discrete(name='quality_generator', values=(x,self.qualDist))

    def generateQualityValue(self):
        return int(self.qualGen.rvs())


if __name__ == "__main__":
    eg = ErrorGenerator(qDist=[0.45, 0.45, 0.05, 0.05]);
    qs = []
    for i in range(40):
        qs.append(eg.generateQualityValue())
    print(qs)

    
