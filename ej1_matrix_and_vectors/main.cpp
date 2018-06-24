#include <vector>
#include <iostream>
#include "main.h"

int main() {
  // Vector containing some integers
  std::vector<int> v = {4, 12, 14, 34, 66};

  // print the items
  for (int n : v) {
    std::cout << n << '\n';
  }

}
