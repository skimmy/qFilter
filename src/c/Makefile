SRC_BASIC=main.cpp fasta_reader.cpp read_sorter.cpp 
SRC_UTIL=util/debug.cpp
SRC_FAST=util/fast/Format.cpp
SRC_SEQUENCE=util/sequence/Read.cpp util/sequence/FastqRead.cpp

ALL_SRC=$(SRC_BASIC) $(SRC_UTIL) $(SRC_FAST) $(SRC_SEQUENCE)

HDR_BASIC=fasta_read.hpp read_sorter.hpp
HDR_UTIL=util/debug.hpp util/stxxl_helper.hpp
HDR_FAST=util/fast/Format.hpp
HDR_SEQUENCE=util/seq.hpp util/sequence/Sequence.hpp util/sequence/Read.cpp util/sequence/Read.hpp util/sequence/FastqRead.hpp

ALL_HDR=$(HDR_BASIC) $(HDR_UTIL) $(HDR_SEQUENCE) $(HDR_FAST)


OUT=reader.out

GXX=g++

DEPENDENCIES=$(ALL_SRC) $(ALL_HDR)

# Options
WARNINGS=-Wall
OPTIMIZATIONS=-O3
DEBUG=-g
COMPATIBILITY=-std=c++11

# Conditional compiler options
VERBOSE=-DVERBOSE=1

ALL_CONDITIONALS=$(VERBOSE)

ALL_OPTIONS_DEBUG=$(WARNINGS) $(OPTIMIZATIONS) $(DEBUG) $(ALL_CONDITIONALS) $(COMPATIBILITY)
ALL_OPTIONS_RELEASE=$(OPTIMIZATIONS) $(COMPATIBILITY)

$(OUT): $(ALL_SRC) 
	$(GXX) $(ALL_OPTIONS_DEBUG) $(ALL_SRC) -o $(OUT)

clean: $(OUT)
	rm -rf $(OUT)
