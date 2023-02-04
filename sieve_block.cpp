#include <iostream>
#include <cmath>
#include <mpi.h>
using namespace std;

int N = 100;
int main(int argc, char *argv[])
{

	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
	int arr[N] = {0};
	//Division of array
	int elemnt_per_process = (N - 2) / size;
	int start_index = rank * elemnt_per_process + 2;
	int end_index = start_index + elemnt_per_process;
	if (rank == size - 1)
	{
		end_index = start_index + elemnt_per_process + ((N - 2) % size);
	}

	//Sieves Algorithm
	for (int i = 2; i <= N; i++)
	{

		if (arr[i] == 0)
		{

			for (int j = start_index + 1; j <= end_index; j += 1)
			{

				if ((j % i == 0) && j >= i * i)
				{

					arr[j] = 1;
				}
			}
		}
	}

	for (int i = start_index; i <= end_index; i++)
	{
		if (arr[i] == 0)
		{
			cout <<"Prime number ["<<i<<"]"<< " From Process Number[" << rank<<"]"<< endl;
		}
	}

	MPI_Finalize();
	return 0;
}
