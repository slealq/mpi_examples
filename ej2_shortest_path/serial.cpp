#include <iostream>
#include <climits>
#include <algorithm>
#include "serial.h"

int main() {
  // size of the cities graph
  int size = 8;

  // search the shortest path beginning from this city
  int start = 0;

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
  int n=0;

  // fill the options
  for (int i=0; i<size; i++) {
    if (n!=start) {
      // while n is different from start city
      options[i] = n;
    } // if

    // increment n
    n++;
  } // for

  // set the minimum path to the max int size
  int min_path = INT_MAX;

  // while there is not permutation left
  do {
    for (int i=0; i<size; i++) {
      std::cout << options[i];
    }
    std::cout << "\n";

  } while (std::next_permutation(options, options+size-1) );

}
