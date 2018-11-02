#include "pt4.h"
#include "mpi.h"
#include <vector>

void Solve()
{
    Task("MPI4Type22");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int sz = (size - 1) * (size - 1);
	std::vector<double> res(sz);
	std::vector<double> n(size - 1, 0);
	if (rank != 0) {
		for (int i = 0; i < size - 1; ++i) {
			pt >> n[i];
		}
	}
	int d_we;
	MPI_Datatype nt;
	MPI_Type_size(MPI_DOUBLE, &d_we);
	MPI_Type_create_resized(MPI_DOUBLE, 0, d_we * (size - 1), &nt);
	MPI_Type_commit(&nt);
	std::vector<int> sdispls(size, 0);
	std::vector<int> scount(size, (size - 1));
	std::vector<int> rdispls(size, 0);
	for (int i = 2; i < size; ++i) {
		rdispls[i] = (i - 1) * d_we;
	}
	std::vector<int> rcount(size, (size - 1));
	std::vector<MPI_Datatype> stypes(size, MPI_DOUBLE);
	std::vector<MPI_Datatype> rtypes(size, nt);
	MPI_Alltoallw(&n[0], &scount[0], &sdispls[0], &stypes[0], &res[0], &rcount[0], &rdispls[0], &rtypes[0], MPI_COMM_WORLD);
	if (rank == 0) {
		for (auto &i : res) {
			pt << i;
		}
	}
}
