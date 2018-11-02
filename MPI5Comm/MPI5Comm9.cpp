#include "pt4.h"
#include "mpi.h"
#include <vector>

void Solve()
{
    Task("MPI5Comm9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm nc;
	int n;
	pt >> n;
	MPI_Comm_split(MPI_COMM_WORLD, n, rank, &nc);
	if (n) {
		double a;
		pt >> a;
		int nc_size;
		MPI_Comm_size(nc, &nc_size);
		std::vector<double> re(nc_size);
		MPI_Allgather(&a, 1, MPI_DOUBLE, &re[0], 1, MPI_DOUBLE, nc);
		for (auto &i : re) {
			pt << i;
		}
	}
}
