#include <algorithm>
#include <iostream>
#include <omp.h>
using namespace std;
// Function to sort an array using brick sort
int brickSort(int arr[], int N)
{
	// Calculate the number of threads to use
	int num_threads = omp_get_max_threads();

	// Determine the size of each "brick"
	int brick_size = (N + num_threads - 1) / num_threads;

	// Perform bubble sort on each brick in parallel
	#pragma omp parallel for
	for (int i = 0; i < num_threads; i++)
	{
		int start = i * brick_size;
		int end = min(start + brick_size, N);

		for (int j = start; j < end; j++)
			for (int k = j + 1; k < end; k++)
				if (arr[k] < arr[j])
					swap(arr[k], arr[j]);
	}

	// Merge the sorted bricks using bubble sort
	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++)
			if (arr[j] < arr[i])
				swap(arr[j], arr[i]);
}

int main()
{
	int N=5;
	int arr[N] = {5, 3, 2, 4, 1};

	brickSort(arr, N);

	// Print the sorted array
	for (int i=0;i<N;i++)
	{
		cout << arr[i] << " ";
	}
		
	cout <<endl;

	return 0;
}
