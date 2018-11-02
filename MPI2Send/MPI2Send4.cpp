#include "pt4.h"
#include "mpi.h"
#include <vector>
void Solve()
{
    Task("MPI2Send4");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		for (int i = 1; i < size; ++i) {
			int N;
			MPI_Status status;
			MPI_Probe(i, i, MPI_COMM_WORLD, &status);
			MPI_Get_count(&status, MPI_INT, &N);
			std::vector<int> ans(N);
			MPI_Recv(&ans[0], N, MPI_INT, i, i, MPI_COMM_WORLD, &status);
			int sz = ans.size();
			for (int i = 0; i < sz; ++i) {
				pt << ans[i];
			}
		}
		
	}
	else if (rank != 0) {
		int N;
		pt >> N;
		std::vector<int> z(N);
		for (int i = 0; i < N; ++i) {
			pt >> z[i];
		}
		int buffsize = N * sizeof(int) + MPI_BSEND_OVERHEAD;
		int *buff = (int *)malloc(buffsize);
		MPI_Buffer_attach(buff, buffsize);
		MPI_Bsend(&z[0], N, MPI_INT, 0, rank, MPI_COMM_WORLD);
		MPI_Buffer_detach(buff, &buffsize);
	}
}
