# makefile for ej3
# @Author Giancarlo Marin H.
# @Date 24/06/2018
# @Brief UCR - IE0521 - T2EJ3 - PRIMES

CC = g++
CXX = mpic++
CFLAGS = -c -Wall 
SER = serial.out
PAR = parallel.out

.PHONY: clean

all: serial parallel

run: runSer runPar

serial: ej3_primes_sec.o
	$(CC) -o serial.out ej3_primes_sec.o

parallel: ej3_primes_par.o
	$(CXX) -o parallel.out ej3_primes_par.o

ej3_primes_sec.o : ej3_primes_sec.cpp 
	$(CC) $(CFLAGS) ej3_primes_sec.cpp
	@echo 'Succesful Compile: Primes Sec...'

ej3_primes_par.o : ej3_primes_par.cpp
	$(CXX) $(CFLAGS) ej3_primes_par.cpp
	@echo 'Succesful Compile: Primes Parallel...'

# The upper limit for the 500000 prime is calculated based on the approximation of Prime(500000)=7368787. source: http://www.wolframalpha.com/input/?i=Prime(500000) 
runSer: 
	@echo 'Ej3 - Primes Sequential code in execution for 500000 primes '
	./$(SER) 7368788

runPar: 
	@echo
	@echo 'Ej3 - Primes Parallel code in execution for 500000 primes: '
	@echo 
	@echo '2 RANKS'
	mpirun -np 2 ./$(PAR) 7368788	
	@echo 
	@echo '3 RANKS'
	mpirun -np 3 ./$(PAR) 7368788	
	@echo 
	@echo '4 RANKS'
	mpirun -np 4 ./$(PAR) 7368788	
	@echo 
	@echo '5 RANKS'
	mpirun -np 5 ./$(PAR) 7368788	
	@echo 
	@echo '6 RANKS'
	mpirun -np 6 ./$(PAR) 7368788	
	@echo 
	@echo '7 RANKS'
	mpirun -np 7 ./$(PAR) 7368788	
	@echo 
	@echo '8 RANKS'
	mpirun -np 8 ./$(PAR) 7368788	
	@echo 
	@echo '9 RANKS'
	mpirun -np 9 ./$(PAR) 7368788	
	@echo 
	@echo '10 RANKS'
	mpirun -np 10 ./$(PAR) 7368788	

runTestSer:
	@echo 'Ej3 - Primes Serial code in execution for user define primes '
	./$(SER) ${L}	

runTestPar:
	@echo 'Ej3 - Primes Parallel code in execution for user define primes '
	mpirun -np ${RANKS} ./$(PAR) ${L}	

clean: 
	rm *.o *.out	
	@echo 'Clean dir succesful...'

$(V).SILENT:

# end
