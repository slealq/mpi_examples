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
#define MSG_01 1    //Message for Updating sieve
#define MSG_02 2    //Message for identifying processor
#define MSG_03 3    //Message for identifying processor
#define KILL  99    //Message for identifying processor


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
* @param int limit      (Max value of sieve)
* @param bool* sieveA   (Original sieve)
*/
void Atkin(int x, int limit, bool* sieveA){
    for (int y = 1; y*y < limit; y++) {
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

void printAtking(bool* sieveA, int limit){
    for (int i = 0; i < limit; ++i)
    {
        printf("%d ",sieveA[i]);
    }
    printf("\n");
}


/*
 * MAIN drive of the programm
 *
 */
int main(int argc, char **argv){
    int startT = clock();
    // Initialize with 0
    int limit = 0;
    if (argc > 1) {
        limit = atoi(argv[1]);
    }
    int rank, size, proc, cont, work, kills,x,r;
    bool subAtkin, subRoots, subPrint, kill; 
    bool sieve[limit], sieveA[limit];
    MPI_Init(&argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    subAtkin = true;
    subPrint = false;
    cont = 2;
    kills = 0;
    while(subAtkin){
        // Master distribute work
        if (rank==0){
            //Initilise the sieve with false values
            for (int i = 0; i < limit; i++){
                sieve[i] = false;
                sieveA[i] = false;
            }
            x = 1;
            int all = false;
            while(x*x < limit){
                work = true;
                if (!all){
                    //Asign work linear for 1st time
                    for (int i = 1; i < size; ++i){
                        MPI_Send(&work, 1, MPI_INT, i, MSG_00, MPI_COMM_WORLD);
                        MPI_Send(&sieveA, limit, MPI_INT, i, MSG_01, MPI_COMM_WORLD);
                        MPI_Send(&x,1,MPI_INT,i,MSG_03,MPI_COMM_WORLD);
                        x++;        
                    }
                    all = true;
                }
                else{
                    //Asign work as soon as slaves is not busy
                    MPI_Recv(&proc,1,MPI_INT,MPI_ANY_SOURCE,MSG_02,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                    MPI_Recv(&sieveA,limit,MPI_INT,proc,MSG_01,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                    for (int i = 0; i < limit; i++){
                        sieve[i] |= sieveA[i];
                    }
                    printf("rank %d sieve\n", rank);
                    printAtking(sieve,limit);
                    MPI_Send(&work, 1, MPI_INT, proc, MSG_00, MPI_COMM_WORLD);
                    MPI_Send(&sieveA, limit, MPI_INT, proc, MSG_01, MPI_COMM_WORLD);
                    MPI_Send(&x,1,MPI_INT,proc,MSG_03,MPI_COMM_WORLD);
                    x++;
                }
            }
            work = false;
            //Killing all processors linearly
            for (int j = 1; j < size; ++j){
                MPI_Send(&work, 1, MPI_INT, j, MSG_00, MPI_COMM_WORLD);     
            }
            subAtkin = false;
            subRoots = true;
        }
        //slaves behaviour
        else{
            MPI_Recv(&work,1,MPI_INT,0,MSG_00,MPI_COMM_WORLD,MPI_STATUS_IGNORE);            
            if (work){
                MPI_Recv(&sieveA,limit,MPI_INT,0,MSG_01,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                MPI_Recv(&x,1,MPI_INT,0,MSG_03,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                Atkin(x,limit,sieveA);
                printf("rank %d sieve\n", rank);
                printAtking(sieveA,limit);
                proc = rank;
                MPI_Send(&proc, 1, MPI_INT, 0, MSG_02, MPI_COMM_WORLD);
                MPI_Send(&sieveA, limit, MPI_INT, 0, MSG_01, MPI_COMM_WORLD);           
                work = false;   
            }
            else{
                subAtkin = false;
                subRoots = true;
            }
        }
    }
    while(subRoots){
        if (rank==0){
            printf("rank %d sieve\n", rank);
            printAtking(sieve,limit);
            r = 5;
            int all = false;
            work = true;
            for (int i = 0; i < limit; i++){
                sieveA[i] ^= sieve[i];
            }
            while(r*r < limit){
                if (!all){
                    //Asign work linear
                    for (int i = 1; i < size; ++i){
                        MPI_Send(&work, 1, MPI_INT, i, MSG_00, MPI_COMM_WORLD);
                        MPI_Send(&sieveA, limit, MPI_INT, i, MSG_01, MPI_COMM_WORLD);
                        MPI_Send(&r,1,MPI_INT,i,MSG_03,MPI_COMM_WORLD);
                        r++;        
                    }
                    all = true;
                }
                else{
                    MPI_Recv(&proc,1,MPI_INT,MPI_ANY_SOURCE,MSG_02,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                    MPI_Recv(&sieveA,limit,MPI_INT,proc,MSG_01,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                    for (int i = 0; i < limit; i++){
                        sieve[i] &= sieveA[i];
                    }
                    MPI_Send(&work, 1, MPI_INT, proc, MSG_00, MPI_COMM_WORLD);
                    MPI_Send(&sieveA,limit,MPI_INT,proc,MSG_01,MPI_COMM_WORLD);
                    MPI_Send(&r,1,MPI_INT,proc,MSG_03,MPI_COMM_WORLD);
                    r++;
                }
            }
            work = false;
            //Killing all processors linearly
            for (int j = 1; j < size; ++j){
                MPI_Send(&work, 1, MPI_INT, j, MSG_00, MPI_COMM_WORLD);     
            }
            subRoots = false;
            subPrint = true;
        }
        else{
            MPI_Recv(&work,1,MPI_INT,0,MSG_00,MPI_COMM_WORLD,MPI_STATUS_IGNORE);            
            if (work){
                MPI_Recv(&sieveA,limit,MPI_INT,0,MSG_01,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                MPI_Recv(&r,1,MPI_INT,0,MSG_03,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                // Determining non-prime all multiples of squares. Starting with 5
                for (int i = r*r; i < limit; i += r*r){
                    sieveA[i] = false;
                }
                proc = rank;
                MPI_Send(&proc, 1, MPI_INT, 0, MSG_02, MPI_COMM_WORLD);
                MPI_Send(&sieveA, limit, MPI_INT, 0, MSG_01, MPI_COMM_WORLD);
                work = false;   
            }
            else{
                subRoots = false;
                MPI_Send(&proc, 1, MPI_INT, 0, KILL, MPI_COMM_WORLD);           
            }
        }
    }
    kills = 1;
    while (subPrint){
        if (kills == size){
            subPrint = false;
        }
        else{
            // MPI_Recv(&proc, 1, MPI_INT, MPI_ANY_SOURCE, MSG_02, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            // MPI_Recv(&sieveA, limit, MPI_INT, proc, MSG_01, MPI_COMM_WORLD,MPI_STATUS_IGNORE);           
            MPI_Recv(&proc, 1, MPI_INT, MPI_ANY_SOURCE, KILL, MPI_COMM_WORLD,MPI_STATUS_IGNORE);            
            kills++;
        }
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