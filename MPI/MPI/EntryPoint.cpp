#include <iostream>
#include <mpi.h>

#ifdef _WIN32
#pragma comment(lib,"msmpi.lib")
#endif

using namespace std;

void main(int args, char **argv)
{
	int size,rank;
	if (MPI_Init(&args, &argv))
	{printf("MPI_Init error\n"); return;}
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	printf("Size: %d Rank %d\n", size,rank);
	
	MPI_Finalize();
}
