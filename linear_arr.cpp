#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv)
{

    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int N = 16;
    int *Arr = new int[N];// malloc memory allocation
    if(rank==0)
    {
        for (int i = 0; i < N; i++)
    {
        cout<<"Enter Next Element -> ";
        cin>>Arr[i];
    }
    }
    int global_count;
    int count = 0;
    const int M = N / (size-1);
    int recv_arr[M];

    MPI_Scatter(Arr, M, MPI_INT, recv_arr, M, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < M; i++)
    {
        if (recv_arr[i] == 4)
        {
            count++;
        }
    }
    cout << "Occurence Founded by Process[" << rank << "]:" << count << endl;

    MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        cout << "Total sum of Occurences :: " << global_count << endl;
        cout << endl;
    }
    MPI_Finalize();
}