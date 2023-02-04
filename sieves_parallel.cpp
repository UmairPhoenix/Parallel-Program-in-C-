// #include <mpi.h>
// #include <iostream>
// #include <cmath>
// using namespace std;
// const int N = 30;

// int main(int argc, char *argv[])
// {
//     bool *prime = new bool[N + 1];
//     int rank, size;
//     MPI_Init(&argc, &argv);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);

//     if (rank == 0)
//     {

//         for (int i = 0; i <= N; i++)
//         {
//             prime[i] = true;
//         }
//         prime[0] = false;
//         prime[1] = false;
//     }
//     // Calculate block size for each process
//     const int M = N / size;
//     int start = rank * M;
//     int end = start + M - 1;
//     if (rank == size - 1)
//     {
//         end = N;
//     }
//     if (rank != 0)
//     {
//         for (int p = 2; p <= sqrt(N); p++)
//         {
//             if (prime[p])
//             {

//                 for (int i = p * p; i <= N; i += p)
//                 {
//                     prime[i] = false;
//                 }
//             }
//         }
//         MPI_Bcast(&prime, M, MPI_C_BOOL, rank, MPI_COMM_WORLD);
//     }
//     // Gather results from all processes using MPI_Bcast

    

//     // Print all prime numbers
//     if (rank == 0)
//     {
//         for (int p = 2; p <= N; p++)
//         {
//             if (prime[p] = true)
//                 cout << p << " ";
//         }
//     }

//     MPI_Finalize();
//     return 0;
// }
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

int main(int argc, char** argv) {
  // Initialize MPI
  MPI_Init(&argc, &argv);

  // Get the rank (process ID) and size (number of processes)
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Create the array to be sorted and initialize it with random values
  int a[N]={4,5,1,3,2};
  

  // Distribute the array to all the processes using MPI_Scatter
  int local_a[N/size];
  MPI_Scatter(a, N/size, MPI_INT, local_a, N/size, MPI_INT, 0, MPI_COMM_WORLD);

  // Sort the local portion of the array using odd-even sort
  int sorted = 0;
  while (!sorted) {
    sorted = 1;
    for (int i = 0; i < N/size-1; i++) {
      if (i % 2 == 0) {
        // Compare even-indexed elements
        if (local_a[i] > local_a[i+1]) {
          // Swap the elements
          int temp = local_a[i];
          local_a[i] = local_a[i+1];
          local_a[i+1] = temp;
          sorted = 0;
        }
      } else {
        // Compare odd-indexed elements
        if (local_a[i] > local_a[i+1]) {
          // Swap the elements
          int temp = local_a[i];
          local_a[i] = local_a[i+1];
          local_a[i+1] = temp;
          sorted = 0;
        }
      }
    }
  }

  // Gather the sorted local portions of the array using MPI_Gather
  int sorted_a[N];
  MPI_Gather(local_a, N/size, MPI_INT, sorted_a, N/size, MPI_INT, 0, MPI_COMM_WORLD);

  // Print the sorted array on the root process
  if (rank == 0) {
    printf("Sorted array: ");
    for (int i = 0; i < N; i++) {
      printf("%d ", sorted_a[i]);
    }
    printf("\n");
  }

  // Finalize MPI
  MPI_Finalize();
  return 0;
}