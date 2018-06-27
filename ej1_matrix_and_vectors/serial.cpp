#include <iostream>
#include "serial.h"

int main() {
  // Vector containing some integers
  int v[] = {12, 10, 7};

  // Matrix with integers
  int m[3][3] = {{2,4,3}, {1,5,7}, {0,2,3}};

  // vector times matrix, result in r
  int r[3] = {0,0,0};

  // define size
  int v_size = 3;

  std::cout << "Vector contents: \n";

  // print the items
  for (int n : v) {
    std::cout << n << '\n';
  }

  std::cout << "Matrix contents: \n";

  // print the items
  for (int i=0; i<v_size; i++) {
    for (int n : m[i]) {
      std::cout << n << '\n';
    }
    std::cout << ",\n";
  }

  // iterate over each column of the matrix
  for (int i=0; i<v_size; i++) {
    // iterate over each pos of vector and matrix
    for (int j=0; j<v_size; j++) {
      r[i] += v[j] * m[i][j];
    }
  }

  std::cout << "Result: \n";

  // print the result
  for (int n : r) {
    std::cout << n << "\n";
  }

  return 0;

}
