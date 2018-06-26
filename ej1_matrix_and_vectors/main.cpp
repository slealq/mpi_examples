#include <iostream>
#include "main.h"
#include "serial.h"
#include "parallel.h"

int main(int argc, char *argv[]) {
  // Vector containing some integers
  int v[] = {12, 10, 7};

  // print the items
  for (int n : v) {
    std::cout << n << '\n';
  }

  // Matrix with integers
  int m[3][3] = {{2,4,3}, {1,5,7}, {0,2,3}};

  // print the items
  for (int i=0; i<3; i++) {
    for (int n : m[i]) {
      std::cout << n << '\n';
    }
  }

  // vector times matrix, result in r
  int r[3] = {0,0,0};

  // use the serial function
  serial(v, m, r, 3);

  // print the result
  for (int n : r) {
    std::cout << n << "\n";
  }

  // test mpi test function
  parallel_mpi(argc, argv);

  return 0;

}
