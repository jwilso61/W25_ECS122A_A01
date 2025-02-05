/*
Given tree T w/ n vertices numbered 1, 2, . . . n.
Find tree diameter.
Diameter: the maximum distance among all pairs of vertices in the tree.
The distance between two vertices is the number of edges on the shortest path between them.

(Hint). Let u be any vertex in the tree and v be the farthest vertex from u. If there are several
candidates for v, choose any. Let w be the farthest vertex from v (if there are several such vertices,
choose any). The diameter is equal to the distance between v and w. 

Note that this fact can be used to design a linear time algorithm to compute the diameter.
Remark 1: For this question, your program will be tested against multiple test instances within a
single test file. Each test instance contains the description of a tree T.
Remark 2: For this problem, we recommend implementing breadth-first search for finding v and w.
If you implement depth-first search using recursion, your program may crash if the recursion is too
deep. This is because the maximum call stack size is 10 MB on Gradescope, and the default maximum
depth of recursive calls in Python is 1000.

Each input file contains several test instances. 
The first line = single integer C = number of test instances your program is tested against. 
The description of the P instances follows.
Each test instance is formatted as follows. The first line = integer n = number of vertices in tree T. 
Each of the subsequent n−1 lines contains a pair of space-separated integers u and v, 
indicating that there is an edge between vertex u and vertex v in T.
For each test instance, your program should output a single integer: the diameter of the tree T.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u;
    int v;
} Edge;

int compute_diameter(int n, Edge *T) {
    int visTot = 0;
    int d1, d2 = 0;
    Edge *pT = T;

    int *visited = calloc(n, sizeof(int));
    if (visited == NULL) { 
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 0;
    };
    int *pV = visited;

    *pV = pT->u;
    pV++;
    *pV = pT->v;

    while (pV != NULL){
        while (pT != NULL){
            if (pT->u == *pV) {
                pV = pT->v; 
                visTot++;
            }
            else if (pT->v == *pV) {
                pV = pT->u; 
                visTot++;
            }
            pT++;
        }
        pT = T+1;
    }
    

    free(visited);
    return 0;
}

int main(void) {
    int testCases;
    scanf("%d", &testCases);

    for (int t = 0; t < testCases; t++) {
        int n;
        scanf("%d", &n);

        Edge *T = (Edge *)malloc((n-1) * sizeof(Edge));
        if (T == NULL) { 
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 0;
        };

        for (int i = 0; i < n - 1; i++) {
            scanf("%d %d", &T[i].u, &T[i].v);
        }

        int answer = compute_diameter(n, T);
        printf("%d\n", answer);

        free(T);
    }

    return 0;
}