##
# First example for mpi using vector and matrix
#
# @file
# @version 0.1

CC = g++
CFLAGS = -c -Wall

all: main

hello : main.o
	$(CC) -o main main.o

main.o : main.cpp
	$(CC) $(CFLAGS) main.cpp

clean : 
	rm *.o main


# end
