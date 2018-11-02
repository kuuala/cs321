#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send17");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int temp_in = 0;
	int temp_out = 0;
	for (int i = 0; i < size - 1; ++i) {
		int in;
		pt >> in;
		if (temp_in == rank) {
			++temp_in;
		}
		MPI_Send(&in, 1, MPI_INT, temp_in, 0, MPI_COMM_WORLD);
		int out;
		if (temp_out == rank) {
			++temp_out;
		}
		MPI_Status status;
		MPI_Recv(&out, 1, MPI_INT, temp_out, 0, MPI_COMM_WORLD, &status);
		pt << out;
		++temp_in;
		++temp_out;
	}
}
