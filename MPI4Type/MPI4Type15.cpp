#include "pt4.h"
#include "mpi.h"
#include <vector>

void Solve()
{
    Task("MPI4Type15");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		int sz = (size - 1) * (size - 1);
		std::vector<double> n(sz);
		for (int i = 0; i < sz; ++i) {
			pt >> n[i];
		}
		MPI_Datatype nt;
		int temp;
		MPI_Type_size(MPI_DOUBLE, &temp);
		MPI_Type_create_resized(MPI_DOUBLE, 0, temp * (size - 1), &nt);
		MPI_Type_commit(&nt);
		for (int i = 1; i < size; ++i) {
			MPI_Send(&n[i - 1], (size - 1), nt, i, 0, MPI_COMM_WORLD);
		}
	}
	else {
		std::vector<double> res(size - 1);
		MPI_Status stat;
		MPI_Recv(&res[0], (size - 1), MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
		for (auto &i : res) {
			pt << i;
		}
	}
}
