#include <mpi.h>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 10;

int main(int argc, char **argv)
{
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the rank (process ID) and size (number of processes)
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Create the array to be sorted and initialize it with random values
    int Arr[N] = {9, 7, 8, 6, 5, 4, 3, 2, 0, 1};
    const int M = N / size;
    // Array that will go to the processes
    int recv_arr[M];
    // Sort the array using odd-even sort
    MPI_Scatter(Arr, M, MPI_INT, recv_arr, M, MPI_INT, 0, MPI_COMM_WORLD);
    // Sorting Performed
    cout << "Array Received by Process[" << rank << "]";
    for (int i = 0; i < M; i++)
    {
        cout << " " << recv_arr[i];
    }
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < M; j += 2)
            {
                // Compare even-indexed elements
                if (recv_arr[i] > recv_arr[i + 1])
                {

                    swap(recv_arr[j], recv_arr[j + 1]);
                }
            }
        }
        else
        {
            for (int j = 1; j < M; j += 2)
            {
                // Compare odd-indexed elements
                if (recv_arr[i] > recv_arr[i + 1])
                {
                    // Swap the elements
                    swap(recv_arr[j], recv_arr[j + 1]);
                }
            }
        }
    }
    cout << "Sorted Array " << endl;
    for (int i = 0; i < M; i++)
    {
        cout << " " << Arr[i];
    }
    cout << endl;
    // MPI_Gather(recv_arr,M,MPI_INT,Arr,M,MPI_INT,0,MPI_COMM_WORLD);
    // // Print the sorted array
    // if (rank == 0)
    // {
    //     cout << "Sorted Array " << endl;
    //     for (int i = 0; i < N; i++)
    //     {
    //         cout << "\t" << Arr[i];
    //     }
    //     cout<<endl;
    // }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}