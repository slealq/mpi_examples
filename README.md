# mpi_examples
Programming examples using C++ and MPI comparing the serial case against the parallel case with MPI. This is a homework assignment of the course Estructuras de Computadores II of the Universidad de Costa Rica.

# Dependencies
The code was tested in an Arch Linux environment, using g++ version 8.1.1 and MPI version 3.1.

For Debian and alike systems, use:

	sudo apt install mpich

For Arch Linux and alike systems, use:
	
	sudo aurman -S openmpi
	
Remember to have your g++ up-to-date.

# Compiling and running

For examples 1 and 2 you should use make to compile, and run with:

To compile:
	make
	
To run:
	
	./serial.out  

	mpiexec -n 4 ./parallel.out

For example 3:

To copile:
	
	make

To run:
	
	make run
	
