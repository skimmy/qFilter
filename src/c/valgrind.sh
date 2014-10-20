clear
valgrind --leak-check=yes --track-origins=yes ./reader.out -X -M 100000 ~/filtering/data/ecoli_600x_.read1_tagged.fastq
