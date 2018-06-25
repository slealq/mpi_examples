##
# First example for mpi using vector and matrix
#
# @file
# @version 0.1

CC = g++
CFLAGS = -c -Wall

all: main

main : main.o
	$(CC) -o main main.o serial.o

main.o : main.cpp
	$(CC) $(CFLAGS) main.cpp

serial.o : serial.cpp
	$(CC) $(CFLAGS) serial.cpp

clean : 
	rm *.o main


# end
