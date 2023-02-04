//In this Code, I Hard coded the Array
#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv)
{
    //mpiexec -np 4 
    MPI_Init(&argc, &argv);
    int rank, size;// size =4
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // P0,P1,P2,P3
    MPI_Comm_size(MPI_COMM_WORLD, &size); //size == 4
    const int N = 16;//Array Division
    int Arr[N] = {1, 1, 2, 2, 4, 4, 4, 4, 1, 4, 2, 2, 5, 5, 5, 5};
    int global_count;
    int count = 0;// Process ka apna apna Variable
    const int M = N / size; // Divide into Equal Number of Chunks
    int recv_arr[M]; // Child Array
    //Divide Data into equal chunks
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