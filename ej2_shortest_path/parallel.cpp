#include <mpi.h>
#include <iostream>
#include "parallel.h"

int main(int argc, char *argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (size < 2) {
    std::cout << "More processes needed to run ...\n";
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  if (rank==0) {
    // len of the cities graph
    int len = 8;

    // search the shortest path beginning from this city
    // this doesn't really matter, since starting from anywhere
    // leads to the same best roundtrip
    int start = 0;

    // another example
    // int len = 4;
    // int cities[len][len] = { { 0, 10, 15, 20 },
    //                   { 10, 0, 35, 25 },
    //                   { 15, 35, 0, 30 },
    //                   { 20, 25, 30, 0 } };


    // define the cities weight
    int cities[len][len] = { {0, 115, 8, 17, 167, 26, 83, 75},
                             {115, 0, 120, 129, 272, 92, 197, 100},
                             {8, 120, 0, 9, 160, 34, 78, 83},
                             {17, 129, 9, 0, 151, 43, 69, 91},
                             {167, 272, 160, 151, 0, 193, 98, 236},
                             {26, 92, 34, 43, 193, 0, 108, 55},
                             {83, 197, 78, 69, 98, 108, 0, 141},
                             {75, 100, 83, 91, 236, 55, 141, 0} };
  } // rank 0 code

} // main
