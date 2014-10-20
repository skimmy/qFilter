clear
valgrind --leak-check=yes --track-origins=yes ./reader.out -M 1 ~/filtering/data/ecoli_600x_.read1_tagged.fastq
