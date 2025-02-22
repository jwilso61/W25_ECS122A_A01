
/*
n villages
m roads
Roads connect pairs of villages
Not all villages have wells
At start no roads and wells exist.

GOVERNMENT REQIREMENT: Upon rebuild, travel from each village to at least one village with a well should be possible. 
Road and well cost varies. 

Given the cost of rebuilding each road and well, compute a minimum-cost reconstruction plan.

Compute the answer in O(mlog n) time.

Each input file contains several test instances. 
The very first initial line = single integer C = number of test instances.
The description of the C instances and their format follows.
The first line contains two integers n (villages) and m (roads). The villages are numbered 1, 2, . . . , n. 
The second line contains n space-separated integers w1,w2, . . . ,wn.
If the ith integer is positive, then there was a well at village i before the earthquake, and it costs wi dollars to rebuild this
well; otherwise, wi must be −1, indicating that there is no well in the ith village.
Each of the subsequent m lines contains three space-separated integers u, v, and c (1 ≤ u, v ≤ n),
indicating that there is a road between village u and village v, and the cost of rebuilding this road is c dollars.

For each test instance, program output = single integer: the minimum cost for a reconstruction plan that meets the government’s requirements.

1 ≤ n ≤ 1E5.
m ≤ 4E5.
Cost of rebuilding road or well is a positive integer <= 1E9.
For every village u, there exists at least one village v such that:
    (i) u is reachable from v by roads
    (ii) v contains a water well
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct { int u, v, w; } Edge;

// function for qsort: sorts edges by weight (ascending)
int compareEdges(const void *a, const void *b) {
    Edge *ea = (Edge *) a;
    Edge *eb = (Edge *) b;
    return (ea->w - eb->w);
}

// Union-find functions
int find(int *parent, int x) {
    if (parent[x] != x) { parent[x] = find(parent, parent[x]); }
    return parent[x];
}

void unionSets(int *parent, int *rank, int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rootX == rootY) { return; }
    if (rank[rootX] < rank[rootY]) { parent[rootX] = rootY; }
    else if (rank[rootX] > rank[rootY]) { parent[rootY] = rootX; }
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

/*
    1. Each village starts as its own component
       For each village i, record best[i]:
          - If a well can be rebuilt at i, best[i] = weights[i]
          - Otherwise, best[i] = INF
    2. Sort all roads by cost
    3. Process each road in increasing order
    4. For each remaining component, add its best well cost
       (ex building one well per connected group)
       
  Final sum = minimum cost of reconstruction
*/
int64_t computeMinimumCost(int n, int m, int* weights, Edge* originalEdges) {
    const int64_t INF = 1000000000000000000LL; // 1e18 "infinite" cost (no available well)

    // union-find arrays
    int *parent = (int *) malloc((n + 1) * sizeof(int));
    int *rank   = (int *) malloc((n + 1) * sizeof(int));
    
    // store minimum well cost available in village i
    int64_t *best = (int64_t *) malloc((n + 1) * sizeof(int64_t));
        
    for (int i = 1; i <= n; i++) { // Initialize union-find and best array for each village
        parent[i] = i;
        rank[i] = 0;
        if (weights[i] != -1)   { best[i] = weights[i]; }
        else                    { best[i] = INF; }
    }
        
    qsort(originalEdges, m, sizeof(Edge), compareEdges); // Sort the original roads by cost
    
    int64_t cost = 0;
    // Process each road in increasing order
    for (int i = 0; i < m; i++) {
        int u = originalEdges[i].u;
        int v = originalEdges[i].v;
        int w = originalEdges[i].w;
        
        int ru = find(parent, u);
        int rv = find(parent, v);
        if (ru != rv) {
            // Compute the max well cost between the two components
            int64_t maxWell = (best[ru] > best[rv]) ? best[ru] : best[rv];
            // If road cost is <= this maximum, merging is good
            if (w <= maxWell) {
                unionSets(parent, rank, ru, rv);
                int rnew = find(parent, ru); // New representative after union
                int64_t newBest = (best[ru] < best[rv]) ? best[ru] : best[rv];
                best[rnew] = newBest;
                cost += w;
            }
        }
    }
    
    // For each remaining component, add the cost of building the cheapest well in that component
    for (int i = 1; i <= n; i++) {
        if (find(parent, i) == i) {
            if (best[i] == INF) {  // well not avail
                free(parent);
                free(rank);
                free(best);
                return -1;
            }
            cost += best[i];
        }
    }
    
    free(parent);
    free(rank);
    free(best);    
    return cost;
}

int main() {
    int tc;
    if (scanf("%d", &tc) != 1)
        return 1;
    
    for (int t = 0; t < tc; t++) {
        int n, m;
        if (scanf("%d %d", &n, &m) != 2)
            return 1;
        
        // allocate weights array (ignore index 0; villages 1..n)
        int* weights = (int*) malloc((n + 1) * sizeof(int));
        if (!weights) return 1;
        for (int i = 1; i <= n; i++) { scanf("%d", &weights[i]); }
        
        // read m roads
        Edge* edges = (Edge*) malloc(m * sizeof(Edge));
        if (!edges) {
            free(weights);
            return 1;
        }
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        }
        
        int64_t result = computeMinimumCost(n, m, weights, edges);
        printf("%lld\n", result);
        
        free(weights);
        free(edges);
    }
    return 0;
}
