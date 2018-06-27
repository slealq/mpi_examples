#include <iostream>
#include "serial.h"

int main() {
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

  // iterate over each column of the matrix
  for (int i=0; i<3; i++) {
    // iterate over each pos of vector and matrix
    for (int j=0; j<3; j++) {
      r[i] += v[j] * m[i][j];
    }
  }

  // print the result
  for (int n : r) {
    std::cout << n << "\n";
  }

  return 0;

}
