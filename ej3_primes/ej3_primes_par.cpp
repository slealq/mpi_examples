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

#define MSG_00 0    //Message for Assigning Work
#define MSG_01 1    //Message for process x
#define MSG_02 2    //Message for process y
#define MSG_03 3    //Message for identifying processor
#define MSG_04 4    //Message for list of newPrimes
#define KILL  99    //Message for KIlling processor


/*
* Mark sieveA[n] is true if one of the following is true:
* a) n = (4*x^2)+(y^2) has odd number of solutions, i.e., there exist
*   odd number of distinct pairs (x, y) that satisfy the equation and
*   n module 12 = 1 or n module 12 = 5.
* b) n = (3*x^2)+(y^2) has odd number of solutions and n module 12 = 7
* c) n = (3*x*x)-(y^2) has odd number of solutions, where x > y and 
*   n module 12 = 11 
* Source: https://en.wikipedia.org/wiki/Sieve_of_Atkin 
*
* @param int x          (Base value)
* @param int y          (Base value)
* @param int limit      (Max value of sieve)
* @return int newPrimes[3]    (List of newPrimes to add in sieve)
*/
void Atkin(int x, int y, int limit, int newPrimes[]){
    newPrimes[0]=0;
    newPrimes[1]=0;
    newPrimes[2]=0;
    int n = (4*x*x) + (y*y);
    if (n <= limit && (n % 12 == 1 || n % 12 == 5)){
        newPrimes[0] = n;
    }
    n = (3*x*x) + (y*y);
    if (n <= limit && n % 12 == 7){
        newPrimes[1] = n;
    }
    n = (3*x*x) - (y*y);
    if (x > y && n <= limit && n % 12 == 11){
        newPrimes[2] = n;
    }
}

void printAtking(bool* sieveA, int limit){
    printf("Sieve: [");
    for (int i = 0; i < limit; ++i)
    {
        printf("%d ",sieveA[i]);
    }
    printf("]\n");
}


/*
 * MAIN drive of the programm. To find primes until a limit number
 * @argv[1] int limit (Max value to search for primes)
 */
int main(int argc, char **argv){
    int startT = clock();
    // Initialize with 0
    int limit = 0;
    if (argc > 1) {
        limit = atoi(argv[1]);
    }
    int rank, size, proc, cont, work, kills, x, y, r, send, recv;
    bool subAtkin, subRoots, subKill; 
    bool sieve[limit];
    int newPrimes[3];
    MPI_Init(&argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    subAtkin = true;
    subRoots = false;
    subKill = false;
    cont = 2;
    kills = 0;
    while(subAtkin){
        // Master distribute work
        if (rank==0){
            //Initilise the sieve with false values
            for (int i = 0; i < limit; i++){
                sieve[i] = false;
            }
            int assign = 1;
            send = 0;
            recv = 0;
            int all = false;
            for(int x=1; x*x < limit; x++){
                for (int y = 1; y*y < limit; y++) {
                    work = true;
                    if (!all){
                        //Asign work linear for 1st time
                        MPI_Send(&work, 1, MPI_INT, assign, MSG_00, MPI_COMM_WORLD);
                        MPI_Send(&x,1, MPI_INT, assign, MSG_01, MPI_COMM_WORLD);
                        MPI_Send(&y,1,MPI_INT,assign,MSG_02,MPI_COMM_WORLD);
                        assign++;
                        send++;
                        if (assign==size){        
                            all = true;
                        }
                    }
                    else{
                        //Asign work as soon as slaves is not busy
                        MPI_Recv(&proc,1,MPI_INT,MPI_ANY_SOURCE,MSG_03,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                        MPI_Recv(&newPrimes,3,MPI_INT,proc,MSG_04,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                        recv++;
                        // //Debugging
                        // printf("rank %d sieve\n", rank);
                        // printAtking(sieve,limit);
                        // printf("rank %d Recv from rank %d sieveA\n", rank, proc);
                        // printAtking(sieveA,limit);
                        for (int i = 0; i < 3; i++){
                            sieve[newPrimes[i]] ^= true;
                        }               
                        // printf("rank %d final sieve\n", rank);    
                        // printAtking(sieve,limit);
                        MPI_Send(&work, 1, MPI_INT, proc, MSG_00, MPI_COMM_WORLD);
                        MPI_Send(&x,1, MPI_INT, proc, MSG_01, MPI_COMM_WORLD);
                        MPI_Send(&y,1,MPI_INT,proc,MSG_02,MPI_COMM_WORLD);
                        send++;
                    }
                }
            }
            work = false;
            //Killing all processors linearly
            for (int j = 1; j < size; ++j){
                MPI_Send(&work, 1, MPI_INT, j, MSG_00, MPI_COMM_WORLD);     
            }
            subAtkin = false;
            subKill = true;
        }
        //slaves behaviour
        else{
            MPI_Recv(&work,1,MPI_INT,0,MSG_00,MPI_COMM_WORLD,MPI_STATUS_IGNORE);            
            if (work){
                MPI_Recv(&x,1,MPI_INT,0,MSG_01,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                MPI_Recv(&y,1,MPI_INT,0,MSG_02,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                //Debug
                // printf("rank %d NW sieveA\n", rank);
                // printAtking(sieveA,limit);
                Atkin(x,y,limit,newPrimes);
                proc = rank;
                MPI_Send(&proc, 1, MPI_INT, 0, MSG_03, MPI_COMM_WORLD);
                MPI_Send(&newPrimes, 3, MPI_INT, 0, MSG_04, MPI_COMM_WORLD);           
                work = false;   
            }
            else{
                subAtkin = false;
                MPI_Send(&proc, 1, MPI_INT, 0, KILL, MPI_COMM_WORLD);
            }
        }
    }
    kills = 1;
    while (subKill){
        if (kills == size){
            subKill = false;
            subRoots = true;
        }
        else{
            MPI_Recv(&proc, 1, MPI_INT, MPI_ANY_SOURCE, KILL, MPI_COMM_WORLD,MPI_STATUS_IGNORE);            
            kills++;
        }
    }
    // Determining non-prime all multiples of squares. Starting with 5
    while(subRoots){
        for (int r = 5; r*r < limit; r++) {
            if (sieve[r]) {
                for (int i = r*r; i < limit; i += r*r)
                    sieve[i] = false;
            }
        }
        subRoots = false;
    }
    MPI_Finalize();
    if (rank==0){
        printf("2 3 ");
        for (int j = 5; j < limit; j++){
            if (sieve[j]){
                printf("%d ",j);
                cont++;
            }
        }
        printf("\nPrimes: %d", cont); 
        printf("\nExecution Time: %fs\n",(double)(clock()-startT)/CLOCKS_PER_SEC);  
    }
    return 0;
}