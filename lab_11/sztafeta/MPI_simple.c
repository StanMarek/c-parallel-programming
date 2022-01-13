#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

int main(int argc, char **argv)
{

  int rank, ranksent, size, source, dest, tag, i, pomocnicza;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int temp = 0;

  if (size > 1)
  {

    if (rank == 0)
    {
      dest = rank + 1;
      tag = 0;
      if (dest == size)
        dest = 0;
      MPI_Send(&temp, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

      int var = rank - 1;
      if (var < 0)
        var = size - 1;
    }
    else
    {
      int var = rank - 1;
      if (var < 0)
        var = size - 1;
      MPI_Recv(&ranksent, 1, MPI_INT, var, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      printf("Proces %d odebral liczbe %d od procesu %d\n", rank, ranksent, var, status.MPI_SOURCE);
      temp = ranksent + 1;
      dest = rank + 1;
      tag = 0;
      if (dest == size)
        dest = 0;
      if (rank != size - 1)
        MPI_Send(&temp, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    }
  }
  else
  {
    printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  MPI_Finalize();

  return (0);
}
