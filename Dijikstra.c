#include <stdio.h>
#include <limits.h>

#define INF 9999
#define MAX 10

int main() {
    int graph[MAX][MAX], dist[MAX], visited[MAX];
    int n, src, i, j, min, u;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge):\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if(graph[i][j] == 0 && i != j)
                graph[i][j] = INF;
        }
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);

    for(i = 0; i < n; i++) {
        dist[i] = graph[src][i];
        visited[i] = 0;
    }
    dist[src] = 0;
    visited[src] = 1;

    for(i = 1; i < n; i++) {
        min = INF;
        for(j = 0; j < n; j++) {
            if(!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        visited[u] = 1;

        for(j = 0; j < n; j++) {
            if(!visited[j] && dist[u] + graph[u][j] < dist[j]) {
                dist[j] = dist[u] + graph[u][j];
            }
        }
    }

    printf("Shortest distances from source %d:\n", src);
    for(i = 0; i < n; i++) {
        printf("To %d = %d\n", i, dist[i]);
    }

    return 0;
}
