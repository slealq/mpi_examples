#include <mpi.h>
#include "parallel.h"

int main(int argc, char *argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  std::cout << "Hello world, i am "
            << rank
            << " of "
            << size
            << '\n';

  if (rank == 0) {
    // this will be the master

    // Vector containing some integers
    int v[] = {12, 10, 7};

    // Matrix with integers
    int m[3][3] = {{2,4,3}, {1,5,7}, {0,2,3}};

    // vector times matrix, result in r
    int r[3] = {0,0,0};

    int n; // initial column to send
    int p = 1; // initial rank to send
    int n_total = 3; // total columns of the matrix, vetor

    bool all=false; // boolean to account if all ranks have been used

    int received = 0; // count how many ranks have sent back their info
    int rpos; // rpos for the response position of the vector
    int result; // result from the other process


    for (n=0; n<n_total; n++) {
      if (!all) {
        // continue sending tasks until ranks are out
        MPI_Send(&n_total, 1, MPI_INT, p, 0, MPI_COMM_WORLD); // tag 0 for size of vector
        MPI_Send(&v, n_total, MPI_INT, p, 1, MPI_COMM_WORLD); // tag 1 will be v
        MPI_Send(&m[n], n_total, MPI_INT, p, 2, MPI_COMM_WORLD); // tag 2 will be m
        MPI_Send(&n, 1, MPI_INT, p, 3, MPI_COMM_WORLD); // tag 3 for the n pos of result

        // increment p
        p++;

        // if there are no more ranks left
        if (p == size) {
          // raise all flag
          all = true;
        } // if p == size
      } // if not all

      else {
        // all ranks have been used
        // receive rank from any process
        MPI_Recv(&p, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&rpos, 1, MPI_INT, p, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // receive which column is this response from
        MPI_Recv(&result, 1, MPI_INT, p, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // receive which is the result of the operation

        // store the result
        r[rpos] = result;

        // increase received
        received ++;

        // since that process is now clean, send another tasks
        MPI_Send(&n_total, 1, MPI_INT, p, 0, MPI_COMM_WORLD); // tag 0 for size of vector
        MPI_Send(&v, n_total, MPI_INT, p, 1, MPI_COMM_WORLD); // tag 1 will be v
        MPI_Send(&m[n], n_total, MPI_INT, p, 2, MPI_COMM_WORLD); // tag 2 will be m
        MPI_Send(&n, 1, MPI_INT, p, 3, MPI_COMM_WORLD); // tag 3 for the n pos of result_
      }// else
    }// for n in vector

    // receive the process that are left
  }

  else { // all slaves

    int n_total;
    int n=0;
    int *v;
    int *m;

    MPI_Recv(&n_total, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // allocate memory for the arrays
    v = new int[n_total];
    m = new int[n_total];

    // receive the info
    MPI_Recv(v, n_total, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(m, n_total, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&n, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::cout << "Received: " << n_total << "\n" ;

  }

  MPI_Finalize();

  return 0;

}
