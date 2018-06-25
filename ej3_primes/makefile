# makefile for ej3
# @Author Giancarlo Marin H.
# @Date 24/06/2018
# @Brief UCR - IE0521 - T2EJ3 - PRIMES

CC = g++
OUTPUT = primes

.PHONY: clean

all: .o run500 clean

.o : 
	$(CC) -o $(OUTPUT) ej3_primes_sec.cpp
	@echo 'Succesful Compile: Primes Sec...'

run500: 
	@echo 'Ej3 - Primes Sequential code in execution for 500000 primes '
	./$(OUTPUT) 7368789

clean : 
	find . -type f -name $(OUTPUT) | xargs rm -rf
	@echo 'Clean dir succesful...'

$(V).SILENT:

# end
