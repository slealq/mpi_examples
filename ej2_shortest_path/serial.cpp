#include <iostream>
#include <climits>
#include <algorithm>
#include "serial.h"

int main() {
  // size of the cities graph
  int size = 8;

  // search the shortest path beginning from this city
  // this doesn't really matter, since starting from anywhere
  // leads to the same best roundtrip
  int start = 0;

  // another example
  // int size = 4;
  // int cities[size][size] = { { 0, 10, 15, 20 },
  //                   { 10, 0, 35, 25 },
  //                   { 15, 35, 0, 30 },
  //                   { 20, 25, 30, 0 } };


  // define the cities weight
  int cities[size][size] = { {0, 115, 8, 17, 167, 26, 83, 75},
                             {115, 0, 120, 129, 272, 92, 197, 100},
                             {8, 120, 0, 9, 160, 34, 78, 83},
                             {17, 129, 9, 0, 151, 43, 69, 91},
                             {167, 272, 160, 151, 0, 193, 98, 236},
                             {26, 92, 34, 43, 193, 0, 108, 55},
                             {83, 197, 78, 69, 98, 108, 0, 141},
                             {75, 100, 83, 91, 236, 55, 141, 0} };

  // options of cities, to permutate
  int options[size-1];

  // number of city to fill in options
  int n=0; // start with 0

  // fill the options
  for (int i=0; i<size; i++) {
    if (i!=start) {
      // while n is different from start city
      options[n] = i;

      // increase n
      n++;
    } // if
  } // for

  // set the minimum path to the max int size
  int min_path = INT_MAX;
  int min_option[size-1];

  // define variables for the loop
  int current_city;
  int current_pathweight;

  // while there is not permutation left
  do {
    // reset current path weight
    current_pathweight=0;

    // define the current city as the starting point
    current_city=start;

    // find current path weight
    for (int i=0; i<size-1; i++) {
      // use options array to chose next city
      current_pathweight += cities[current_city][options[i]];

      // update current city
      current_city = options[i];
    }

    // add the return, from last option to start
    current_pathweight += cities[current_city][start];

    //min_path = std::min(min_path, current_pathweight);

    // update the minimum path
    if (std::min(min_path, current_pathweight) == current_pathweight) {
      //update minimu path
      min_path = current_pathweight;

      // save the path
      for (int i=0; i<size-1; i++) {
        min_option[i] = options[i];
      }
    }

  } while (std::next_permutation(options, options+size-1) );

  // now finish by printing the result

  // print the minum path weight
  std::cout << "Minimum path weight is: " << min_path << " \n";

  // also print the minimum path
  std::cout << "The round trip is the following: ";

  std::cout << start;
  std::cout << ",";

  for(int i=0; i<size-1; i++) {
    std::cout << min_option[i];
    std::cout << ",";
  }

  std::cout << start;
  std::cout << "\n";

}
