##
# First example for mpi using vector and matrix
#
# @file
# @version 0.1

CC = g++
CXX = mpic++
CFLAGS = -c -Wall
CXXFLAGS = -c -Wall

all: main

main : main.o serial.o parallel.o
	$(CXX) -o main main.o serial.o parallel.o

main.o : main.cpp
	$(CC) $(CFLAGS) main.cpp

serial.o : serial.cpp serial.h
	$(CC) $(CFLAGS) serial.cpp

parallel.o : parallel.cpp parallel.h
	$(CXX) $(CXXFLAGS) parallel.cpp

clean : 
	rm *.o main


# end
