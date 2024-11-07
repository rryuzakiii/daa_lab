// Aim of the program: Given an undirected weighted connected graph G(V, E). Apply
// Krushkal’s algorithm to
// ● Find the minimum spanning tree T(V, E’) and Display the selected edges of G.
// ● Display total cost of the minimum spanning tree T.
// Note# Nodes will be numbered consecutively from 1 to n (user input), and edges will have
// varying weight. The weight matrix of the graph can be represented from the user’s input in the
// given format. The expected output could be the selected edge and the corresponding cost of the
// edge as per the sample output.
// Input Format:
// ● The first line contains two space-separated integers ‘n’ and ‘m’, the number of nodes
// and edges in the graph.
// Each line ‘i’ of the ‘m’ subsequent lines contains three space-separated integers ‘u’, ‘v’
// and ‘w’, that describe an edge (u, v) and weight ‘w’.
// Input:
// 9 14
// 1 2 4
// 1 8 8
// 2 3 8
// 2 8 11
// 3 4 7
// 3 6 4
// 3 9 2
// 4 5 9
// 4 6 14
// 5 6 10
// 6 7 2
// 7 8 1
// 7 9 6
// 8 9 7
// Output:
// Edge Cost
// 8--7 1
// 7--6 2
// 3--9 2
// 1--2 4
// 3--6 4
// 3--4 7
// 1--8 8
// 4--5 9
// Total Weight of the Spanning Tree: 37

#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 100

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    Edge edges[MAX_EDGES];
    int edgeCount;
} EdgeList;

// Function prototypes
int findParent(int parent[], int i);
void unionSets(int parent[], int rank[], int x, int y);
int compareEdges(const void *a, const void *b);

int main() {
    int n, m;
    printf("Enter number of nodes and edges: ");
    scanf("%d %d", &n, &m);

    EdgeList edgeList;
    edgeList.edgeCount = m;

    printf("Enter the edges (u, v, weight):\n");
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edgeList.edges[i].u, &edgeList.edges[i].v, &edgeList.edges[i].weight);
    }

    // Sort edges based on weight
    qsort(edgeList.edges, edgeList.edgeCount, sizeof(edgeList.edges[0]), compareEdges);

    int parent[n + 1], rank[n + 1];
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int totalCost = 0;
    printf("\nEdge Cost\n");

    for (int i = 0; i < edgeList.edgeCount; i++) {
        int u = edgeList.edges[i].u;
        int v = edgeList.edges[i].v;
        int weight = edgeList.edges[i].weight;

        int parentU = findParent(parent, u);
        int parentV = findParent(parent, v);

        // If including this edge does not cause a cycle
        if (parentU != parentV) {
            printf("%d--%d %d\n", u, v, weight);
            totalCost += weight;
            unionSets(parent, rank, parentU, parentV);
        }
    }

    printf("Total Weight of the Spanning Tree: %d\n", totalCost);
    return 0;
}

int findParent(int parent[], int i) {
    if (parent[i] != i) {
        parent[i] = findParent(parent, parent[i]); // Path compression
    }
    return parent[i];
}

void unionSets(int parent[], int rank[], int x, int y) {
    if (rank[x] < rank[y]) {
        parent[x] = y;
    } else if (rank[x] > rank[y]) {
        parent[y] = x;
    } else {
        parent[y] = x;
        rank[x]++;
    }
}

int compareEdges(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}
