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

  if (rank==0) {
    // master rank

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
    } // if
  } // for

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
      received ++;

      // since that process is now clean, send another tasks
    } // else


  } while (std::next_permutation(options, options+len-1));

  // receive the process that are left

  // kill all slaves

  // print the result

  } // rank 0 code

  else { // all slaves

    while (1) {

      // wait for work signal or kill signal

      // do work

      // send back result

    } // while ever

  } // else

  MPI_Finalize();
  return 0;

} // main
