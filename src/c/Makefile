SRC=fasta_reader.cpp read_sorter.cpp util/debug.cpp
HDR=fasta_read.h read_sorter.h util/debug.h
OUT=reader.out

GXX=g++

DEPENDENCIES=$(SRC) $(HDR)

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

$(OUT): $(SRC) 
	$(GXX) $(ALL_OPTIONS_DEBUG) $(SRC) -o $(OUT)

clean: $(OUT)
	rm -rf $(OUT)
