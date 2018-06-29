#include <mpi.h>
#include <iostream>
#include <algorithm>
#include <climits>
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

  // len of cities graph
  const int len=8;

  // define the cities weight
  int cities[len][len] = { {0, 115, 8, 17, 167, 26, 83, 75},
                           {115, 0, 120, 129, 272, 92, 197, 100},
                           {8, 120, 0, 9, 160, 34, 78, 83},
                           {17, 129, 9, 0, 151, 43, 69, 91},
                           {167, 272, 160, 151, 0, 193, 98, 236},
                           {26, 92, 34, 43, 193, 0, 108, 55},
                           {83, 197, 78, 69, 98, 108, 0, 141},
                           {75, 100, 83, 91, 236, 55, 141, 0} };

  if (rank==0) {
    // master rank

    // search the shortest path beginning from this city
    // this doesn't really matter, since starting from anywhere
    // leads to the same best roundtrip
    int start = 0;

    // options of cities, to permutate
    int options[len-1];

    // number of city to fill in options
    int n=0; // start with 0

    // fill the options
    for (int i=0; i<len; i++) {
      if (i!=start) {
        // while n is different from start city
        options[n] = i;

        // increase n
        n++;
      } // if (condition) {

    }//for

    // set the minimum path to the max int len
    int min_path = INT_MAX;
    int min_option[len-1];

    // define variables for the loop
    int current_city;
    int current_pathweight;

    // variables for the master
    int p=1; // rank to send code to
    bool all=false; // all ranks have been used for the first times
    int work=1; // work for slaves
    int received=0; // count how many ranks have sent back their info

    // while there is not permuatation left
    do {
      if (!all) {
        // continue sending tasks until ranks are out
        MPI_Send(&work, 1, MPI_INT, p, 10, MPI_COMM_WORLD); // tag 10 work bool
        MPI_Send(&options, len-1, MPI_INT, p, 0, MPI_COMM_WORLD); // tag 0 for options permutation

        // send the permutation of options, and let the slave do the calculation

        // increment p
        p++;

        // if there are no more ranks left
        if (p==size) {
          // raise all flag
          all = true;
        } // if p == size
      } // if not all

      else {
        // all ranks have been used
        // receive rank from any process

        // we have to receive the min path weight, and the min path

        // increase received
        break;
        received ++;

        // since that process is now clean, send another tasks
      } // else

    } while (std::next_permutation(options, options+len-1));

    // receive the process that are left

    // kill all slaves
    work = 0;
    for (int i=0; i<size; i++) {
      MPI_Send(&work, 1, MPI_INT, i, 10, MPI_COMM_WORLD); // send kill
    }

    // print the result

  } // rank 0 code

  else { // all slaves
    int work;
    int *options;
    int current_pathweight;
    int current_city;

    while (1) {
      // wait for work signal or kill signal

      MPI_Recv(&work, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // receive signal to work
      if (work==0) {
        break;
      }

      // allocate memory for the array
      options = new int[len-1];

      // do work
      MPI_Recv(options, len-1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // receive the option

      for (int i=0; i<len-1; i++) {
        std::cout << options[i];
      }
      std::cout << "\n";

      // reset current path weight
      current_pathweight=0;

      // define the current city as the starting point

      // send back result

    } // while ever

  } // else

  MPI_Finalize();
  return 0;

} // main
