#include <vector>
#include <iostream>
#include "main.h"

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


}