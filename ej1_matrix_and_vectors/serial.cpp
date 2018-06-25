#include "serial.h"

int *serial(int[] v, int[][] m, int *size) {
  int r[3] = {0,0,0};

  // iterate over each column of the matrix
  for (int i=0; i<3; i++) {
    // iterate over each pos of vector and matrix
    for (int j=0; j<3; j++) {
      r[i] += v[j] * m[j][i];
    }
  }


}
