#include "pt4.h"
#include "mpi.h"
#include <vector>

void Solve()
{
    Task("MPI3Coll12");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> n(4);
	for (int i = 0; i < 4; ++i) {
		pt >> n[i];
	}
	int t = 4 * size;
	std::vector<int> res(t);
	MPI_Allgather(&n[0], 4, MPI_INT, &res[0], 4, MPI_INT, MPI_COMM_WORLD);
	for (auto &i : res) {
		pt << i;
	}
}
