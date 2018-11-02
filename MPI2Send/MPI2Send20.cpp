#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send20");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		for (int i = 1; i < size; ++i) {
			double temp;
			MPI_Status status;
			MPI_Recv(&temp, 1, MPI_DOUBLE, MPI_ANY_SOURCE, i, MPI_COMM_WORLD, &status);
			pt << temp;
		}
	}
	else {
		int N;
		double A;
		pt >> A;
		pt >> N;
		MPI_Send(&A, 1, MPI_DOUBLE, 0, N, MPI_COMM_WORLD);
	}
}
