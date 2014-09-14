SRC=fasta_reader.c read_sorter.c util/debug.c
HDR=fasta_read.h read_sorter.h util/debug.h
OUT=reader.out

GXX=g++

DEPENDENCIES=$(SRC) $(HDR)

# Options
WARNINGS=-Wall
OPTIMIZATIONS=-O3
DEBUG=-g

ALL_OPTIONS=$(WARNINGS) $(OPTIMIZATIONS) $(DEBUG)

$(OUT): $(SRC) 
	$(GXX) $(ALL_OPTIONS) $(SRC) -o $(OUT)

clean: $(OUT)
	rm -rf $(OUT)
