#include <stdio.h>

#include "dijkstra_module.h"

int main() {
    int vertices;

    // Input the number of vertices
    printf("Input the number of vertices: ");
    scanf("%d", &vertices);

    if (vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Invalid number of vertices. Exiting...\n");
        return 1;
    }

    int graph[MAX_VERTICES][MAX_VERTICES];
	int prev[MAX_VERTICES]; 

    // Input the adjacency matrix representing the weighted graph
    printf("Input the adjacency matrix for the graph (use INT_MAX for infinity):\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int source;

    // Input the source vertex
    printf("Input the source vertex: ");
    scanf("%d", &source);

    if (source < 0 || source >= vertices) {
        printf("Invalid source vertex. Exiting...\n");
        return 1;
    }

	int target;

    // Input the target vertex
    printf("Input the target vertex: ");
    scanf("%d", &target);

    if (target < 0 || target >= vertices) {
        printf("Invalid target vertex. Exiting...\n");
        return 1;
    }

    // Perform Dijkstra's algorithm
    dijkstra(graph, source, target, vertices, prev);

    return 0;
}

