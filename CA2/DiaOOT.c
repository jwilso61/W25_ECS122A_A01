#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u;
    int v;
} Edge;

typedef struct {
    int node;
    int dist;
} BFSResult;

// Returns the furthest node and distance
BFSResult bfs(int start, int n, int **adj, int *adjCount) {
    int *queue = (int *)malloc(n * sizeof(int));
    int *dist = (int *)calloc(n+1, sizeof(int));
    int front, back, maxDist = 0;
    int farthestNode = start;

    queue[back++] = start;
    for (int i = 1; i <= n; i++){dist[i] = -1;}  // Mark all nodes as unvisited
    dist[start] = 0;  // Distance to starting node is 0

    while (front < back) {
        int u = queue[front++];
        for (int i = 0; i < adjCount[u]; i++) {
            int v = adj[u][i];
            if (dist[v] == -1) {  // If v is unvisited
                dist[v] = dist[u] + 1;
                queue[back++] = v;
                
                if (dist[v] > maxDist) { // Update the farthest node
                    maxDist = dist[v];
                    farthestNode = v;
                }
            }
        }
    }
    free(queue);
    free(dist);
    BFSResult result = {farthestNode, maxDist};
    return result;
}

int compute_diameter(int n, Edge *T) {
    // adjacency list
    int **adj = (int **)malloc((n + 1) * sizeof(int *));
    int *adjCount = (int *)calloc(n + 1, sizeof(int));
    
    // Count neighbors and allocate memory for each adjacency list
    for (int i = 0; i < n - 1; i++) {
        adjCount[T[i].u]++;
        adjCount[T[i].v]++;
    }
    for (int i = 1; i <= n; i++) {
        adj[i] = (int *)malloc(adjCount[i] * sizeof(int));
        adjCount[i] = 0;  // Reset for filling in the lists
    }

    // Fill adjacency lists
    for (int i = 0; i < n - 1; i++) {
        int u = T[i].u;
        int v = T[i].v;
        adj[u][adjCount[u]++] = v;
        adj[v][adjCount[v]++] = u;
    }

    BFSResult bfs1 = bfs(T[0].u, n, adj, adjCount); // Search for farthest node X from any arbitrary start (node T[0].u)
    BFSResult bfs2 = bfs(bfs1.node, n, adj, adjCount); // Search from node X to find the farthest node and compute the diameter

    for (int i=1; i<=n; i++) {free(adj[i]);}
    free(adj);
    free(adjCount);

    return bfs2.dist;
}

int main(void) {
    int testCases;
    scanf("%d", &testCases);

    for (int t = 0; t < testCases; t++) {
        int n;
        scanf("%d", &n);

        Edge *T = (Edge *)malloc((n - 1) * sizeof(Edge));
        if (T == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            return 0;
        }

        for (int i = 0; i < n - 1; i++) {
            scanf("%d %d", &T[i].u, &T[i].v);
        }

        int answer = compute_diameter(n, T);
        printf("%d\n", answer);
        free(T);
    }

    return 0;
}