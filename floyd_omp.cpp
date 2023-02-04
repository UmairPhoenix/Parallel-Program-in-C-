#include <iostream>
#include <omp.h>
using namespace std;
const int MAX=10e6;
const int N = 4;

// Floyd algorithm
int floyd(int graph[N][N], int distance[N][N], int next[N][N])
{
  int num_threads = omp_get_max_threads();
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      distance[i][j] = graph[i][j];
      next[i][j] = j;
    }
  }
  // Floyd Updating
  for (int k = 0; k < N; k++)
  {
    #pragma omp parallel for
    cout<<"Thread["<<omp_get_thread_num()<<"]";
    for (int i = 0; i < N; i++)
    {

      for (int j = 0; j < N; j++)
      {
        if (distance[i][k] + distance[k][j] < distance[i][j])
        {
          distance[i][j] = distance[i][k] + distance[k][j];
          next[i][j] = next[i][k];
        }
      }
    }
  }
  
  
  
}

int main()
{
  // Example graph
  int graph[N][N] = {{0, 3, 6, 15},
                     {MAX, 0, -2, MAX},
                     {MAX, MAX, 0, 2},
                     {1, MAX, MAX, 0}};

  // Initialize the distance and next node matrices
  int distance[N][N], next[N][N];

  // Calculate the distance and next node matrices
  floyd(graph, distance, next);

  // Print the distance matrix
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cout << distance[i][j] << ' ';
    }
    cout << endl;
  }
  cout << "\n"
       << "The Updated Matrix"
       << "\n";
  // Print the next node matrix
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cout << next[i][j] << ' ';
    }
    cout << endl;
  }

  return 0;
}
