#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send27");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int n;
	pt >> n;
	if (n == -1) {
		int in_proc = 0;
		for (int i = 0; i < size - 1; ++i) {
			if (in_proc == rank) {
				++in_proc;
			}
			double temp;
			MPI_Status status;
			MPI_Recv(&temp, 1, MPI_DOUBLE, MPI_ANY_SOURCE, in_proc, MPI_COMM_WORLD, &status);
			pt << temp;
			++in_proc;
		}
	}
	else {
		double A;
		pt >> A;
		int iter = 0;
		MPI_Request req;
		MPI_Issend(&A, 1, MPI_DOUBLE, n, rank, MPI_COMM_WORLD, &req);
		MPI_Status status;
		int flag = 0;
		while (flag == 0) {
			MPI_Test(&req, &flag, &status);
			++iter;
		}
		Show(iter);
	}
}
