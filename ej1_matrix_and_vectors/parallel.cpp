#include <mpi.h>
#include "parallel.h"

int main(int argc, char *argv[]) {
  int rank, size;
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  std::cout << "Hello world, i am "
            << rank
            << " of "
            << size
            << '\n';

  if (rank == 0) {
    // im the first rank
    int number = 11;
    MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    std::cout << "I'm rank "
              << rank
              << " sending a message to 1\n";
  }

  else if (rank == 1) {
    int number;
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "Process 1 received data : "
              << number
              << " \n";
  }

  MPI_Finalize();

  return 0;

}
