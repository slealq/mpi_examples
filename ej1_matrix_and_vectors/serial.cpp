#include "serial.h"

int serial(int v[], int m[3][3], int r[], int size) {
  /* This function will assume that the matrix and
     vector are the same size, and can be multiplied.
   */

  // iterate over each column of the matrix
  for (int i=0; i<size; i++) {
    // iterate over each pos of vector and matrix
    for (int j=0; j<size; j++) {
      r[i] += v[j] * m[j][i];
    }
  }

  return 1; // return true for success
}
