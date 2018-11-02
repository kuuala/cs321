#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm20");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm nc, nc_sub;
	int res[4];
	int z;
	pt >> z;
	int dims[] = { 2, 2, size / 4 },
		periods[] = { 0, 0, 0 },
		remain_dims[] = { 1, 1, 0 };
	MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, 0, &nc);
	MPI_Cart_sub(nc, remain_dims, &nc_sub);
	MPI_Gather(&z, 1, MPI_INT, res, 1, MPI_INT, 0, nc_sub);
	int rank_sub;
	MPI_Comm_rank(nc_sub, &rank_sub);
	if (rank_sub == 0) {
		for (auto &i : res) {
			pt << i;
		}
	}
}
