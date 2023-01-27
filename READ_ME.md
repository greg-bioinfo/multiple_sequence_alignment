# implementation in C++ of a multiple alignment algorithm using the progressive method by ascending hierarchical classification

the algorithm is implemented in the 'alignment.cpp' program.
First compile the program with the functions:

g++ -c fonction_alignment.cpp

Then compile the main program: 

g++ fonction_alignment.o alignment.cpp -o alignment.exe

You can use this program to align any sequence whose events are separated by a space.
The first argument is the file with the traces, the second is the file where you want to write your alignments, the third is the csv file that will contains the score then its the deletion penalty, insertion penalty, the threshold, the match score and mismatch score:

./alignment.exe trace.txt alignment.txt score.csv 0 0 10 15 5

The program 'data_generation.cpp' allows to generate traces with random events:

g++ -c fonction_data.cpp

g++ fonction_data.o data_generation.cpp -o data_generation.exe

The first argument of the program is the file where are the parameters and the second is the prefix of each file where will be written traces:

./data_generation.exe parameters.txt align.txt

To automatically generate a certain number of traces and align them according to several parameters use the program 'launch.py':

All the generated files will be put in the result directory.
The first argument of the program is the file where are the parameters, the second one is the prefix of the files that will contain the traces,
the third one one is the prefix of the files that will contain the alignment, the last one is the file that will contain the score


python ./launch.py parameters.txt trace_txt align.txt score.csv

