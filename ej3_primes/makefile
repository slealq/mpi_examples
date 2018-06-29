# makefile for ej3
# @Author Giancarlo Marin H.
# @Date 24/06/2018
# @Brief UCR - IE0521 - T2EJ3 - PRIMES

CC = g++
CXX = mpic++
CFLAGS = -c -Wall 
OUTPUT = serial.out

.PHONY: clean

all: serial parallel

run: run500

serial: ej3_primes_sec.o
	$(CC) -o serial.out ej3_primes_sec.o

parallel: ej3_primes_par.o
	$(CXX) -o parallel.out ej3_primes_par.o

ej3_primes_sec.o : ej3_primes_sec.cpp 
	$(CC) $(CFLAGS) ej3_primes_sec.cpp
	@echo 'Succesful Compile: Primes Sec...'

ej3_primes_par.o : ej3_primes_par.cpp
	$(CXX) $(CFLAGS) ej3_primes_par.cpp

# The upper limit for the 500000 prime is calculated based on the approximation of Prime(500000)=7368787. source: http://www.wolframalpha.com/input/?i=Prime(500000) 
run500: 
	@echo 'Ej3 - Primes Sequential code in execution for 500000 primes '
	./$(OUTPUT) 7368788

clean : 
	rm *.o *.out	
	@echo 'Clean dir succesful...'

$(V).SILENT:

# end
