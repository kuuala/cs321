#include "pt4.h"
#include "mpi.h"
#include <vector>

template<typename T>
void sendrecv(int rank, int size, MPI_Datatype d, int step) {
	int next = (rank + step) % size;
	if (next < 0) {
		next += size;
	}

	int n = size / 2;
	std::vector<T> z(n);
	for (int i = 0; i < n; ++i) {
		pt >> z[i];
	}

	MPI_Status status;
	MPI_Sendrecv_replace(&z[0], n, d, next, 0, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

	for (auto &i : z) {
		pt << i;
	}
}

void Solve()
{
    Task("MPI2Send24");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank % 2 == 0) {
		sendrecv<double>(rank, size, MPI_DOUBLE, 2);
	}
	else {
		sendrecv<int>(rank, size, MPI_INT, -2);
	}
}
