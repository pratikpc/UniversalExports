// Reference: https://www.hackerearth.com/practice/algorithms/graphs/hamiltonian-path/practice-problems/algorithm/micro-and-coins/description/

//Micro was playing with a graph gifted to him by his friend on his birthday.The graph contains N vertices
// and M edges.All the edges are bidirectional.On each vertex of the graph there is a coin.
// Now Micro has to collect them all.But the game has some rules.
// The player has to start with some vertex.From current vertex, player can visit only those vertices
// which are connected to it by an edge.Also if a vertex is visited it cannot be visited again.
// Now Micro wants to find if he'll be able to collect all the coins.

//Output:
//  For each test case, if Micro is able to collect all the coins then print "Yes" (without quotes) otherwise print "No" (without quotes).

#include<stdio.h> 
#include <stdlib.h>
#include <limits.h>

int CheckIfPartOfHamiltonianPath (int const currentVertex, int const** const graph, int const* const visited, int const pos)
{
   if (!graph[visited[pos - 1]][currentVertex])
      return 0;

   for (int i = 0; i < pos; i++)
      if (visited[i] == currentVertex)
         return 0;
   return 1;
}

int FindHamiltonianPath (int const** const graph, int* visited, int const pos, int const maxVertexCount)
{
   if (pos == maxVertexCount)
      return 1;
   //return (graph[visited[pos - 1]][visited[0]] != 0);

   for (int vertexIt = 1; vertexIt < maxVertexCount; vertexIt++)
      if (CheckIfPartOfHamiltonianPath (vertexIt, graph, visited, pos))
      {
         visited[pos] = vertexIt;
         if (FindHamiltonianPath (graph, visited, pos + 1, maxVertexCount))
            return 1;
         visited[pos] = INT_MIN /*No Path Found. Reset*/;
      }
   return 0;
}

void DisplayHamiltonPath (int const* visited, int const maxVertexCount) {
   for (int i = 0; i < maxVertexCount; i++)
      if (visited[i] != INT_MIN)
         printf (" %d ", visited[i]);
   printf (" %d ", visited[0]);
   printf ("\n");
}

int PerformHamiltonianPathOperation (int const** const graph, int const maxVertexCount)
{
   int* visited = calloc (maxVertexCount, sizeof (int));
   if (visited == NULL)
      return 0;
   for (int i = 1; i < maxVertexCount; i++)
      visited[i] = INT_MIN;
   visited[0/*First*/] = 0/*First Visits First*/;

   return (FindHamiltonianPath (graph, visited, 1/*Find from Second Pos*/, maxVertexCount));
}

//Input:
//First line consists of an integer T denoting the number of test cases.
//First line of each test case consists of
// two space separated integers denoting N and M.
//  The following M lines consists of
//   Two space separated integers X and Y denoting
//   there is an edge between vertices X and Y.
int main () {
   int T;
   scanf ("%d", &T);
   for (int i = 0; i < T; ++i) {
      int M, N;
      scanf ("%d %d", &N, &M);

      int** graph = calloc (N, sizeof (int*));
      if (graph == NULL)
         return;
      for (int j = 0; j < N; ++j)
      {
         graph[j] = calloc (N, sizeof (int));
         if (graph[j] == NULL)
            return;
         for (int k = 0; k < N; ++k)
            graph[j][k] = 0;
      }
      for (int j = 0; j < M; ++j)
      {
         int x, y;
         scanf ("%d %d", &x, &y);
         graph[x - 1][y - 1] = 1;
         graph[y - 1][x - 1] = 1;
      }
      if (PerformHamiltonianPathOperation (graph, N))
         printf ("Yes\n");
      else
         printf ("No\n");
      for (int j = 0; j < N; ++j)
         free (graph[j]);
      free (graph);
   }

   return 0;
}
