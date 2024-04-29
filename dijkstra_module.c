#include <stdio.h>
#include <limits.h>	//INT_MAX

#include "dijkstra_module.h"

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int sptSet[], int vertices) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < vertices; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to print the constructed distance array
void printSolution(int dist[], int vertices) {
    printf("Vertex \tDistance from Source\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d \t%d\n", i, dist[i]);
    }
}

// Function to print the shortest path from source vertex to target
void printShortestPath(int prev[], int dist[], int src, int target) {
	int u = target;

    printf("Shortest path from source %d to target %d (in reverse order):\n",
			src, target);

	// if prev[u] is defined OR u=source
	if(prev[u] != -1 || u == src)
	{
		while(u != -1)	// while u is defined
		{
			printf("Node %d \t at distance %d\n", u, dist[u]);
			u = prev[u];
		}
	}
}

// Function to implement Dijkstra's algorithm for a given graph and source vertex
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src, int target, int
		vertices, int prev[MAX_VERTICES]) {

    int dist[MAX_VERTICES]; // The output array dist[i] holds the shortest distance from src to i
    int sptSet[MAX_VERTICES]; // sptSet[i] will be true if vertex i is included in the shortest path tree or the shortest distance from src to i is finalized

	// prev[i] contains the previous-hop node on the shortest path from source 
	// to the given vertex i
    //int prev[MAX_VERTICES]; 
	

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
		prev[i] = -1;		// -1 = UNDEFINED vertex
        sptSet[i] = 0;
    }

    // Distance from source vertex to itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < vertices - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        // u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, vertices);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < vertices; v++) {
            // Update dist[v] only if it is not in the sptSet, there is an edge from u to v,
            // and the total weight of path from src to v through u is smaller than the current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
				prev[v] = u;
            }
        }
    }

    // Print the constructed distance array
    //printSolution(dist, vertices);

	// Print shortest path to target vertex
	//printShortestPath(prev, dist, src, target);
}

