/*
 *Universidad de Costa Rica - Escuela de Ingenieria Electrica
 *Tarea #2 - IE-0521 - Ej3
 *@author Giancarlo Marin
 *@date   24-06-2018
 *@brief  Generator of the first 500000 prime numbers sequential code implementing the Sieve of Atkin
*/
#include <mpi.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

#define MSG_ARRAY 0
#define MSG_01 1
#define MSG_BOOL 2

using namespace std;

/*
 * Main driver
*/
int main(int argc, char* argv[]){
    int startT = clock();
    // Initialize MPI vars
    int rank, size, x, r, cont;
    MPI_Status status;
    MPI_Init(&argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize with 0
    int limit = 0;
    if (argc > 1) {
      limit = atoi(argv[1]);
    }

    bool sieveA[limit];
    // Array of ranks to determine who is busy. 1 busy and 0 otherwise
    bool busy_rank[size];
    for (int j = 0; j < size; j++){
        busy_rank[j] = false;
    }
    bool work = false;
    while (work){
        if (rank == 0){
            // Initialise the sieve array with false values
            for (int i = 0; i < limit; i++){
                sieveA[i] = false;
            }
            // 2 and 3 are known to be prime
            cont = 2;
            for (int x = 1; x*x < limit; x++) {
                //Asigning job to the first avilable rank
                int k=1;
                while (busy_rank[k]){
                    k++;
                    if (k>size-1){
                        k=1;
                    }
                }
                busy_rank[k]=true;
                MPI_Send(sieveA, limit, MPI_INT, k, MSG_ARRAY, MPI_COMM_WORLD);
                MPI_Send(&x, 1, MPI_INT, k, MSG_01, MPI_COMM_WORLD);
                MPI_Send(busy_rank, size, MPI_INT, k, MSG_BOOL, MPI_COMM_WORLD);
            }
            work = false;
        }
        else {
            MPI_Recv(sieveA,limit,MPI_INT,0,MSG_ARRAY,MPI_COMM_WORLD,&status);
            MPI_Recv(&x,limit,MPI_INT,0,MSG_01,MPI_COMM_WORLD,&status);
            MPI_Recv(busy_rank, size, MPI_INT, 0, MSG_BOOL, MPI_COMM_WORLD,&status);
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
            busy_rank[rank]=false;
        }
    }
    work = false;
    while (work){
        if (rank == 0){
            // Determining non-prime all multiples of squares. Starting with 5
            for (int r = 5; r*r < limit; r++) {
                //Asigning job to the first avilable rank
                int k=1;
                while (busy_rank[k]){
                    k++;
                    if (k>size-1){
                        k=1;
                    }
                }
                busy_rank[k]=true;
                MPI_Send(sieveA, limit, MPI_INT, k, MSG_ARRAY, MPI_COMM_WORLD);
                MPI_Send(&r, 1, MPI_INT, k, MSG_01, MPI_COMM_WORLD);
                MPI_Send(busy_rank, size, MPI_INT, k, MSG_BOOL, MPI_COMM_WORLD);
            }
            work = false;
        }
        else {
            MPI_Recv(sieveA,limit,MPI_INT,0,MSG_ARRAY,MPI_COMM_WORLD,&status);
            MPI_Recv(&r,limit,MPI_INT,0,MSG_01,MPI_COMM_WORLD,&status);
            MPI_Recv(busy_rank, size, MPI_INT, 0, MSG_BOOL, MPI_COMM_WORLD,&status);
            if (sieveA[r]) {
                for (int i = r*r; i < limit; i += r*r)
                    sieveA[i] = false;
            }
            busy_rank[rank]=false;
        }
    }
    if (rank==0){
        // Print primes using sieveA[]
        for (int j = 5; j < limit; j++){
            if (sieveA[j]){
                std::cout << j << " ";
                cont++;
            }
        }
        if (limit > 2)
            std::cout << 2 << " ";
        if (limit > 3)
            std::cout << 3 << " ";
        std::cout << endl << "Primes: " << cont;
        std::cout << endl << "Execution Time: " << (double)(clock()-startT)/CLOCKS_PER_SEC << "s" << endl;
    }

    MPI_Finalize();
    return 0;
}
