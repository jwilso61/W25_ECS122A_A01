#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int n, k;
long long A[MAX_N];

long long compute_min_radius() {
    if (n <= k) return 0; // trivial case
    
    long long left = 0;
    long long right = A[n - 1] - A[0]; // maximum possible distance

    while (left < right) { // binary search for a minimum q
        long long q = (left + right) / 2;
        int towersPlaced = 0;
        int leftMost = 0; // index of the leftmost uncovered city
        
        while (leftMost < n) { // greedy tower placement
            towersPlaced++;
            if (towersPlaced > k) { left = q+1; break; } // too many towers, increase q
            
            int start = leftMost; // start at leftmost uncovered city
            int c = start; //used for coverage checks
            while (c+1 < n && A[c+1] - A[start] <= q) { c++; } //place tower farthest right w/coverage at leftMost
            
            long long coverageEnd = A[c] + q;
            while (leftMost < n && A[leftMost] <= coverageEnd) { leftMost++; } //move past covered cities
        } 
        if (towersPlaced <= k) right = q; // valid q, try smaller
    }
    return left;
}

int main() {
    int C;
    scanf("%d", &C);
    while (C--) {
        scanf("%d %d", &n, &k);

        // Skip percentages, only solving for subtask
        for (int i = 0; i < n; i++) {
            int unused;
            scanf("%d", &unused);
        }
        
        for (int i = 0; i < n; i++) {
            long long pos;
            scanf("%lld", &pos);
            A[i] = pos * 60; // avoids floating point calculations
        }
        printf("%lld\n", compute_min_radius());
    }
    return 0;
}
