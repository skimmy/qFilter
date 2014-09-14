SRC=fasta_reader.c read_sorter.c
HDR=fasta_read.h read_sorter.h
OUT=reader.out

DEPENDENCIES=$(SRC) $(HDR)

# Options
WARNINGS=-Wall
OPTIMIZATIONS=-O3
DEBUG=-g

ALL_OPTIONS=$(WARNINGS) $(OPTIMIZATIONS) $(DEBUG)

$(OUT): $(SRC) 
	gcc $(ALL_OPTIONS) $(SRC) -o $(OUT)
