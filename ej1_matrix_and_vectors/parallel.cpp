#include <mpi.h>
#include "parallel.h"

int parallel_mpi(int argc, char *argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  std::cout << "Hello world, i am "
            << rank
            << " of "
            << size
            << '\n';

  MPI_Finalize();

  return 0;

}