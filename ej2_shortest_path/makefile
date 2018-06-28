##
# First example for mpi using vector and matrix
#
# @file
# @version 0.1

CC = g++
CXX = mpic++
CFLAGS = -c -Wall
CXXFLAGS = -c -Wall

all: serial parallel

serial : serial.o 
	$(CC) -o serial.out serial.o 

parallel : parallel.o
	$(CXX) -o parallel.out parallel.o

serial.o : serial.cpp serial.h
	$(CC) $(CFLAGS) serial.cpp

parallel.o : parallel.cpp parallel.h
	$(CXX) $(CXXFLAGS) parallel.cpp

clean : 
	rm *.o *.out


# end
