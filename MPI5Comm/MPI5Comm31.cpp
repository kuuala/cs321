#include "pt4.h"
#include "mpi.h"
#include <vector>

void Solve()
{
    Task("MPI5Comm31");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int a;
	pt >> a;
	int res = a;
	MPI_Comm nc;
	int sz = 2 * size / 3;
	int sz_d = 0;
	std::vector<int> sources(sz),
		degrees(sz);
	int ind = 0;
	for (int i = 0; i < size; ++i) {
		if (i % 3 == 2) {
			continue;
		}
		sources[ind] = i;
		++ind;
	}
	for (int i = 0; i < sz; ++i) {
		if (sources[i] % 3 == 1) {
			degrees[i] = 1;
			++sz_d;
		}
		else {
			degrees[i] = 3;
			sz_d += 3;
		}
	}
	int cur_v = 0,
		help = 0;
	std::vector<int> destinations(sz_d);
	for (int i = 0; i < sz_d; ++i) {
		if (help < 3) {
			destinations[i] = (sources[cur_v] + help + 1) % size;
			++help;
		}
		else {
			++cur_v;
			help = 0;
			destinations[i] = sources[cur_v] + 1;
			++cur_v;
		}
	}
	int wow = rank == 0 ? sz : 0;
	MPI_Dist_graph_create(MPI_COMM_WORLD, wow, &sources[0], &degrees[0], &destinations[0], MPI_UNWEIGHTED, MPI_INFO_NULL, 0, &nc);
	int in, out, j;
	MPI_Dist_graph_neighbors_count(nc, &in, &out, &j);
	std::vector<int> in_n(in),
		in_w(in);
	int out_s = out == 0 ? 1 : out;
	std::vector<int>
		out_n(out_s),
		out_w(out_s);
	MPI_Dist_graph_neighbors(nc, in, &in_n[0], &in_w[0], out, &out_n[0], &out_w[0]);
	if (out != 0) {
		for (auto &i : out_n) {
			MPI_Send(&a, 1, MPI_INT, i, 0, nc);
		}
	}
	for (auto &i : in_n) {
		MPI_Status st;
		int temp;
		MPI_Recv(&temp, 1, MPI_INT, i, 0, nc, &st);
		res += temp;
	}
	pt << res;
}
