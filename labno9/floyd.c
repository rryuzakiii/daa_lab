#include <stdio.h>
#include <stdlib.h>

#define INF 1000000  

 
void readGraph(int n, int graph[n][n], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &graph[i][j]);
            if (i != j && graph[i][j] == 0) {
                graph[i][j] = INF;  
            }
        }
    }
    fclose(file);
}

void floydWarshall(int n, int dist[n][n], int next[n][n]) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = k + 1;  
                }
            }
        }
    }
}


void printPath(int u, int v, int next[u][v]) {
    if (next[u][v] == 0) {
        printf("No path\n");
        return;
    }
    printf("Path: %d", u + 1);
    while (u != v) {
        u = next[u][v] - 1;
        printf(" -> %d", u + 1);
    }
    printf("\n");
}


int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int graph[n][n];
    int dist[n][n];
    int next[n][n];

    
    readGraph(n, graph, "inDiAdjMat2.dat");

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] == INF || i == j) {
                next[i][j] = 0;
            } else {
                next[i][j] = j + 1;
            }
        }
    }

    
    floydWarshall(n, dist, next);

    
    printf("Shortest Path Weight Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                printf("%7s", "INF");
            } else {
                printf("%7d", dist[i][j]);
            }
        }
        printf("\n");
    }

   
    int u, v;
    printf("\nEnter the vertices u and v to find path (1-%d): ", n);
    scanf("%d %d", &u, &v);
    u--; v--;  
    if (dist[u][v] == INF) {
        printf("No path exists between %d and %d\n", u + 1, v + 1);
    } else {
        printf("Shortest path distance from %d to %d is %d\n", u + 1, v + 1, dist[u][v]);
        printPath(u, v, next);
    }

    return 0;
}