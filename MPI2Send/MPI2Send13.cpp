#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send13");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int in, out;
	pt >> in;
	int prev_rank = (rank == 0) ? size - 1 : rank - 1;
	int next_rank = (rank + 1) % size;
	if (rank % 2) {
		MPI_Ssend(&in, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD);
		MPI_Status status;
		MPI_Recv(&out, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD, &status);
	}
	else {
		MPI_Status status;
		MPI_Recv(&out, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD, &status);
		MPI_Ssend(&in, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD);
	}
	pt << out;
}
