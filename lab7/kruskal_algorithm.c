// Given an undirected weighted connected graph G(V, E) and starring
// vertex ‘s’. Maintain a Min-Priority Queue ‘Q’ from the vertex set V and apply Prim’s algorithm
// to
// ● Find the minimum spanning tree T(V, E’). Display the cost adjacency matrix of ‘T’.
// ● Display total cost of the minimum spanning tree T.
// Note# Nodes will be numbered consecutively from 1 to n (user input), and edges will have
// varying weight. The graph G can be read from an input file “inUnAdjMat.dat” that contains cost
// adjacency matrix. The expected output could be displayed as the cost adjacency matrix of the
// minimum spanning tree and total cost of the tree.
// Content of the input file “inUnAdjMat.dat” could be
// 0 4 0 0 0 0 0 8 0
// 4 0 8 0 0 0 0 11 0
// 0 8 0 7 0 4 0 0 2
// 0 0 7 0 9 14 0 0 0
// 0 0 0 9 0 10 0 0 0
// 0 0 4 14 10 0 2 0 0
// 0 0 0 0 0 2 0 1 6
// 8 11 0 0 0 0 1 0 7
// 0 0 2 0 0 0 6 7 0
// Input:
// Enter the Number of Vertices: 9
// Enter the Starting Vertex: 1
// Output:
// 0 4 0 0 0 0 0 8 0
// 4 0 0 0 0 0 0 0 0
// 0 0 0 7 0 4 0 0 2
// 0 0 7 0 9 0 0 0 0
// 0 0 0 9 0 0 0 0 0
// 0 0 4 0 0 0 2 0 0
// 0 0 0 0 0 2 0 1 0
// 8 0 0 0 0 0 1 0 0
// 0 0 2 0 0 0 0 0 0
// Total Weight of the Spanning Tree: 37

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

void readGraph(int graph[MAX_VERTICES][MAX_VERTICES], int *n) {
    FILE *file = fopen("inUnAdjMat.dat", "r");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    *n = 0;
    while (fscanf(file, "%d", &graph[*n][*n]) != EOF) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%d", &graph[*n][j]);
        }
        (*n)++;
    }
    fclose(file);
}

void primsAlgorithm(int graph[MAX_VERTICES][MAX_VERTICES], int n, int startVertex) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool inMST[MAX_VERTICES];
    int totalCost = 0;

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
        parent[i] = -1;
    }

    key[startVertex] = 0;
    parent[startVertex] = -1;

    for (int count = 0; count < n - 1; count++) {
        int minKey = INT_MAX, minIndex;

        for (int v = 0; v < n; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        inMST[minIndex] = true;
        totalCost += key[minIndex];

        for (int v = 0; v < n; v++) {
            if (graph[minIndex][v] && !inMST[v] && graph[minIndex][v] < key[v]) {
                key[v] = graph[minIndex][v];
                parent[v] = minIndex;
            }
        }
    }

    // Display the cost adjacency matrix of the MST
    printf("\nCost Adjacency Matrix of the Minimum Spanning Tree:\n");
    int mst[MAX_VERTICES][MAX_VERTICES] = {0};

    for (int i = 1; i < n; i++) {
        mst[parent[i]][i] = graph[parent[i]][i];
        mst[i][parent[i]] = graph[parent[i]][i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mst[i][j]);
        }
        printf("\n");
    }

    printf("Total Weight of the Spanning Tree: %d\n", totalCost);
}

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES] = {0};
    int n;
    int startVertex;

    readGraph(graph, &n);

    printf("Enter the Number of Vertices: %d\n", n);
    printf("Enter the Starting Vertex: ");
    scanf("%d", &startVertex);
    startVertex--;  // Adjust for 0-based index

    primsAlgorithm(graph, n, startVertex);

    return 0;
}
