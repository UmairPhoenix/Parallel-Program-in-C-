#include <iostream>
#include <cstring>
#include <mpi.h>
using namespace std;

int main(int argc, char* argv[]) 
{
    int n=5;
    int arr[n]={4,5,2,1,3};
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Divide the array into chunks and send each chunk to a different process
    int chunk_size = n / size;
    int* chunk = new int[chunk_size];
    MPI_Scatter(arr, chunk_size, MPI_INT, chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process sorts its chunk using the odd-even sort algorithm
    for (int i = 0; i < n; i++) 
    {
        // this if statement is used as switcher between even and odd index swap
        if (i % 2 == 0) 
        {
            // Even Index
            for (int j = 0; j < chunk_size; j += 2) 
            {
                if (chunk[j] > chunk[j + 1]) 
                {
                    swap(chunk[j], chunk[j + 1]); // {4,5,1,2,3}
                }
            }
        } 
        else 
        {
            // Odd Index
            for (int j = 1; j < chunk_size; j += 2) 
            {
                if (chunk[j] > chunk[j + 1]) 
                {
                    swap(chunk[j], chunk[j + 1]); //{4,1,5,2,3}
                }
            }
        }
    }

    // Gather the sorted chunks back into a single array on the root process
    int* sorted_arr = nullptr;
    if (rank == 0) 
    {
        sorted_arr = new int[n];
    }
    MPI_Gather(chunk, chunk_size, MPI_INT, sorted_arr, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // The root process prints the sorted array
    if (rank == 0) 
    {
        cout << "Printing out sorted array:" << endl;
        for (int i = 0; i < n; i++) 
        {
            cout << sorted_arr[i] << " ";
        }
        cout << endl;
        delete[] sorted_arr;
    }

    delete[] chunk;
    MPI_Finalize();
    return 0;
}