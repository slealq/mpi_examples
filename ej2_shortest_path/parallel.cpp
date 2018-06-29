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

  // search the shortest path beginning from this city
  // this doesn't really matter, since starting from anywhere
  // leads to the same best roundtrip
  int start = 0;

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
    int min_path_option[len];

    // define variables for the loop
    int current_city;
    int current_pathweight;

    // variables for the master
    int p=1; // rank to send code to
    bool all=false; // all ranks have been used for the first times
    int work=1; // work for slaves
    int received=0; // count how many ranks have sent back their info
    int min_path_received;
    int *min_options;
    min_options = new int[len-1];

    // while there is not permuatation left
    do {
      if (!all) {
        // continue sending tasks until ranks are out
        MPI_Send(&work, 1, MPI_INT, p, 10, MPI_COMM_WORLD); // tag 10 work bool
        MPI_Send(&p, 1, MPI_INT, p, 5, MPI_COMM_WORLD); // 5 will be the p
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
        MPI_Recv(&p, 1, MPI_INT, MPI_ANY_SOURCE, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //recv 5
        MPI_Recv(&min_path_received, 1, MPI_INT, p, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // min path
        MPI_Recv(min_options, len-1, MPI_INT, p, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // receive the options

        // update the minimum path
        if (std::min(min_path, min_path_received) == min_path_received) {
          //update minimu path
          min_path = min_path_received;

          // save the path
          for (int i=0; i<len-1; i++) {
            min_path_option[i] = min_options[i];
          }
        }

        // increase received
        //break;
        received ++;

        // since that process is now clean, send another tasks
        // continue sending tasks until ranks are out
        MPI_Send(&work, 1, MPI_INT, p, 10, MPI_COMM_WORLD); // tag 10 work bool
        MPI_Send(&p, 1, MPI_INT, p, 5, MPI_COMM_WORLD); // 5 will be the p
        MPI_Send(&options, len-1, MPI_INT, p, 0, MPI_COMM_WORLD); // tag 0 for options permutation
      } // else

    } while (std::next_permutation(options, options+len-1));

    // receive the process that are left
    for(n=0; n<size-1; n++) {
      // we have to receive the min path weight, and the min path
      MPI_Recv(&p, 1, MPI_INT, MPI_ANY_SOURCE, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //recv 5
      MPI_Recv(&min_path_received, 1, MPI_INT, p, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // min path
      MPI_Recv(min_options, len-1, MPI_INT, p, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // receive the options

      // update the minimum path
      if (std::min(min_path, min_path_received) == min_path_received) {
        //update minimu path
        min_path = min_path_received;

        // save the path
        for (int i=0; i<len-1; i++) {
          min_path_option[i] = min_options[i];
        }
      }
    }

    // kill all slaves
    work = 0;
    for (int i=0; i<size; i++) {
      MPI_Send(&work, 1, MPI_INT, i, 10, MPI_COMM_WORLD); // send kill
    }

    // print the result
    // print the minum path weight
    std::cout << "Minimum path weight is: " << min_path << " \n";

    // also print the minimum path
    std::cout << "The round trip is the following: ";

    std::cout << start;
    std::cout << ",";

    for(int i=0; i<len-1; i++) {
      std::cout << min_path_option[i];
      std::cout << ",";
    }

    std::cout << start;
    std::cout << "\n";



  } // rank 0 code

  else { // all slaves
    int work;
    int *options;

    int current_pathweight;
    int current_city;

    int p;

    while (1) {
      // wait for work signal or kill signal

      MPI_Recv(&work, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // receive signal to work
      if (work==0) {
        break;
      }

      // allocate memory for the array
      options = new int[len-1];

      // receive the number of process
      MPI_Recv(&p, 1, MPI_INT, 0, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // receive the number p

      // do work
      MPI_Recv(options, len-1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // receive the option

      // reset current path weight
      current_pathweight=0;

      // define the current city as the starting point
      current_city=start;

      // find current path weight
      for(int i=0; i<len-1; i++) {
        // use options array to choose next city
        current_pathweight += cities[current_city][options[i]];

        // update current city
        current_city = options[i];
      } // for

      // add the return, from the last option
      current_pathweight += cities[current_city][start];

      // send back the result
      MPI_Send(&p, 1, MPI_INT, 0, 5, MPI_COMM_WORLD); // send p
      MPI_Send(&current_pathweight, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
      MPI_Send(options, len-1, MPI_INT, 0, 2, MPI_COMM_WORLD);

    } // while ever

  } // else

  MPI_Finalize();
  return 0;

} // main
