/*Given a directed graph G (V, E) and a starting vertex ‘s’.
●Determine the lengths of the shortest paths from the starting vertex ‘s’ to all other vertices in the graph G using Dijkstra’s Algorithm.
●Display the shortest path from the given source ‘s’ to all other vertices.
Note# Nodes will be numbered consecutively from 1 to n (user input), and edges will have varying distances or lengths. The graph G can 
be read from an input file “inDiAdjMat1.dat” that contains non-negative cost adjacency matrix. The expected output could be 
as
 per the sample format.
Content of the input file “inDiAdjMat1.dat” could be
0	10	0	5	0
0	0	1	2	0
0	0	0	0	4
3	0	9	0	2
7	0	6	0	0

Input:
Enter the Number of Vertices: 5
Enter the Source Vertex: 1
Output:
Source	Destination	Cost	Path
1	1	0	-
1	2	8	1->4->2
1	3	9	1->4->2->3
1	4	5	1->4
1	5	7	1->4->5
*/

#include <stdio.h>
#include <limits.h>
#define INF INT_MAX

int minDistance(int dist[], int sptSet[], int n) {
    int min = INF, min_index;
    for (int v = 0; v < n; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1) return;
    printPath(parent, parent[j]);
    printf("->%d", j + 1);
}

void printSolution(int dist[], int n, int parent[], int src) {
    printf("Source\tDestination\tCost\tPath\n");
    for (int i = 0; i < n; i++) {
        if (i != src) {
            printf("%d\t%d\t\t", src + 1, i + 1);
            if (dist[i] == INF)
                printf("INF\t-");
            else {
                printf("%d\t%d", dist[i], src + 1);
                printPath(parent, i);
            }
            printf("\n");
        }
    }
}

void dijkstra(int graph[100][100], int n, int src) {
    int dist[100];
    int parent[100];
    int sptSet[100]; 

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, sptSet, n);
        sptSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printSolution(dist, n, parent, src);
}

int main() {
    int graph[100][100];
    int n, src;

    FILE *file = fopen("inDiAdjMat1.dat", "r"); // Correct the filename
    if (file == NULL) {
        printf("Error opening file!\n");
        return -1;
    }

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);

    printf("Enter the Source Vertex: ");
    scanf("%d", &src);
    src--; // Adjust for 0-based index

    dijkstra(graph, n, src);

    return 0;
}
