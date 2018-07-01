/*
 *Universidad de Costa Rica - Escuela de Ingenieria Electrica
 *Tarea #2 - IE-0521 - Ej3
 *@author Giancarlo Marin
 *@date   24-06-2018
 *@brief  Generator of the first 500000 prime numbers sequential code implementing the Sieve of Atkin
*/
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;


/* Function that prints the primes found until the number limit. 
 * Returns the amount of primes.
 * 
 * @param  int 	limit
 * @return int 	cont
 */
int Primes(int limit){
    // 2 and 3 are known to be prime
    if (limit > 2)
        std::cout << 2 << " ";
    if (limit > 3)
        std::cout << 3 << " ";
    int cont = 2;

    // Initialise the sieve array with false values
    bool sieveA[limit];
    for (int i = 0; i < limit; i++){
        sieveA[i] = false;
    }

 	/* Description of algorithm:
 		Mark sieveA[n] is true if one of the following is true:
    	a) n = (4*x^2)+(y^2) has odd number of solutions, i.e., there exist
       		odd number of distinct pairs (x, y) that satisfy the equation and
       		n module 12 = 1 or n module 12 = 5.
    	b) n = (3*x^2)+(y^2) has odd number of solutions and n module 12 = 7
    	c) n = (3*x*x)-(y^2) has odd number of solutions, where x > y and 
    		n module 12 = 11 
    	Source: https://en.wikipedia.org/wiki/Sieve_of_Atkin 
 	*/
    for (int x = 1; x*x < limit; x++) {
        for (int y = 1; y*y < limit; y++) {
            // Main part of Sieve of Atkin
            int n = (4*x*x) + (y*y);
            if (n <= limit && (n % 12 == 1 || n % 12 == 5)){
                sieveA[n] ^= true;
            }
            n = (3*x*x) + (y*y);
            if (n <= limit && n % 12 == 7){
                sieveA[n] ^= true;
            }
            n = (3*x*x) - (y*y);
            if (x > y && n <= limit && n % 12 == 11){
                sieveA[n] ^= true;
            }
        }
    }
 
    // Determining non-prime all multiples of squares. Starting with 5
    for (int r = 5; r*r < limit; r++) {
        if (sieveA[r]) {
            for (int i = r*r; i < limit; i += r*r)
                sieveA[i] = false;
        }
    }
 
    // Print primes using sieveA[]
    for (int j = 5; j < limit; j++){
        if (sieveA[j]){
            std::cout << j << " ";
        	cont++;
        }
    }

    // Return the amount of primes
	return cont;
}

/*
 * Main driver of programm
 * Inicia una pelea entre ellos e imprime la info de cada pokemon por turno
*/
int main(int argc, char* argv[]){
	int startT = clock(); 
	// The upper limit is calculated based on the approximation of Prime(500000)=7368787
	// source: http://www.wolframalpha.com/input/?i=Prime(500000) 
	int limit = atoi(argv[1]);
    int primes = Primes(limit);	
    std::cout << endl << "Primes: " << primes; 
    std::cout << endl << "Execution Time Serial: " << (double)(clock()-startT)/CLOCKS_PER_SEC << "s" << endl;
	return 0;
}