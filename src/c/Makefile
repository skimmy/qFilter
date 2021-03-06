# All objcet files
BASIC_OBJS=fasta_reader.o read_sorter.o
UTIL_OBJS=util/debug.o util/options.o util/stxxl_helper.o
LIB_BIO_OBJS=util/sequence/Read.o util/sequence/FastqRead.o util/fast/Format.o
ALL_OBJS=$(BASIC_OBJS) $(UTIL_OBJS) $(LIB_BIO_OBJS)

# All header files
HDR_BASIC=fasta_reader.hpp read_sorter.hpp
HDR_UTIL=util/debug.hpp util/options.hpp util/stxxl_helper.hpp util/common.hpp
LIB_BIO_HDR=util/fast/Format.hpp util/seq.hpp util/sequence/Sequence.hpp util/sequence/Read.cpp util/sequence/Read.hpp util/sequence/FastqRead.hpp
ALL_HDR=$(HDR_BASIC) $(HDR_UTIL) $(LIB_BIO_HDR)

# The main file(s)
MAIN=main.cpp

# Output file(s)
OUT=reader.out

# All dependencies
DEPENDENCIES=$(MAIN) $(ALL_OBJS) $(ALL_HDR)

# Conditional compiler options
VERBOSE=-DVERBOSE=1
MTRACE=#-DMTRACE
ALL_CONDITIONALS=$(VERBOSE) $(MTRACE)

# Options
WARNINGS=-Wall
OPTIMIZATIONS=-O3
DEBUG=-g
COMPATIBILITY=-std=c++11

ALL_OPTIONS_DEBUG=$(WARNINGS) $(OPTIMIZATIONS) $(DEBUG) $(ALL_CONDITIONALS) $(COMPATIBILITY)
ALL_OPTIONS_RELEASE=$(OPTIMIZATIONS) $(COMPATIBILITY)

# dynamic linked libraries
LIBS=-lpthread -lstxxl_debug

# Compiler and flags
CXX=g++
CXXFLAGS=$(ALL_OPTIONS_DEBUG)


$(OUT): $(MAIN) $(ALL_OBJS) $(ALL_HDR)
	$(CXX) $(ALL_OPTIONS_DEBUG) $(MAIN) $(ALL_OBJS) $(LIBS) -o $(OUT)

.PHONY: clean
clean:	
	rm -rf util/sequence/*.o
	rm -rf util/fast/*.o
	rm -rf util/*.o
	rm -rf *.o
	rm -rf $(OUT)

