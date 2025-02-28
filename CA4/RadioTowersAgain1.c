/*
There are n cities located along the x axis with the ith city located at (Ai, 0).
k radio towers are to be built only in cities. 
The towers have pi percent of the same coverage range d in the ith city. 
A tower in a city Ai can provide service to all cities j such that |Ai − Aj | ≤ d · pi/100.
A larger coverage radius d, implies a higher cost for building the radio towers. 
Find the smallest d s.t. for k cities w/ towers all n cities have coverage.

I/O
input:
first line: int C //num of test instances
Each test instance has 3 lines:
    1) int n, k
    2) int p1, ..., pn, where pi ∈ {20, 40, 60, 80, 100}
    3) int Ai, ... //index location of city for all n cities
City locations are in increasing order

C
n k
p1, ..., pn
Ai, ...

output:
int d · 60
*/

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>

/*
compute_min_radius: Given n, k, the percentages, and locations of the cities. Return 60·d = q.

Each city's original position A[i] is multiplied by 60 since q is guaranteed to be an integer, this avoids working with non-integers.

Binary Search:
Variables low and high are used as bounds to search for q. "high" starts as the worst-case reception value of 20%, since a tower covers 
q*20/100 = q/5 distance to each side, to cover the entire range from the first to the last city, q needs to be at least 
5 * (scaledA[n-1] - scaledA[0]). "ans" is initially set to "high" as binary search is used to find the smallest feasible q.
mid is the current candidate for q.

Greedy Feasibility Check:
Counter "towersUsed" starts at the first city. "cur" holds the position of the leftmost city that still needs to be covered.
"bestRight" tracks the furthest right position coverable with a tower placed at a candidate city.
"j" is used to iterate over possible tower positions that can cover "cur".
The inner loop checks cities starting from i where a tower at city j would cover the current city "cur".
For each candidate tower at city j, if the left end of its coverage (scaledA[j] - (mid * P[j] / 100)) is at or before "cur", 
the tower is a candidate. Then for each candidate's right endpoint (scaledA[j] + (mid * P[j] / 100)), update "bestRight" if this 
candidate covers further to the right than any previously.
If after the inner loop, "bestRight" is still less than "cur", then no tower could cover the current city and candidate mid is too small.
Otherwise, towersUsed is incremented to track that a tower was placed.
"i" is incremented forward to skip all cities that are covered by the tower that reaches bestRight.

Binary Search Decision:
After processing all cities (i == n) and no more than k towers are used, candidate mid is feasible.
"ans" is updated to mid and a smaller q is searched for by setting high = mid - 1.
Otherwise, candidate "mid" is too small, low is set to mid + 1 to try a larger candidate.
*/

// uint64_t compute_min_radius(uint32_t *P, long long *A, uint32_t n, uint32_t k) {
//     int64_t *scaledA = malloc(n * sizeof(long long));
//     for (uint32_t i = 0; i < n; i++) { scaledA[i] = A[i] * 60LL; } // Scale city positions by 60

//     // Set up binary search for q 
//     uint64_t low = 0;
//     uint64_t high = 5 * (scaledA[n-1] - scaledA[0]) + 1;
//     uint64_t ans = high;

//     while (low <= high) {
//         uint64_t mid = (low + high) / 2;
        
//         // Greedy feasibility check if all cities with at most k towers be covered by candidate mid
//         uint32_t towersUsed = 0;
//         uint32_t i = 0;
//         while (i < n) {            
//             long long cur = scaledA[i];  //leftmost city yet to be covered
//             long long bestRight = -1;
//             uint32_t j = i;
//             // Try all potential towers that could cover city i
//             while (j < n && (scaledA[j] - (mid * P[j] / 100)) <= cur) {
//                 long long right = scaledA[j] + (mid * P[j] / 100);
//                 if (right > bestRight) { bestRight = right; }
//                 j++;
//             }        
//             if (bestRight < cur) { break; } // If no tower covers cur city, candidate mid fails
//             towersUsed++;
//             while (i < n && scaledA[i] <= bestRight) { i++; } // Skip cities that are covered by the selected tower
//         }        
//         // If we covered all cities (i == n) and used no more than k towers, candidate mid is feasible
//         if (i == n && towersUsed <= k) {
//             ans = mid;
//             high = mid - 1;
//         } 
//         else {low = mid + 1;}
//     }    
//     free(scaledA);
//     return ans;
// }

// int main() {
//     uint32_t tc;
//     scanf("%d", &tc);
    
//     for (uint32_t t=0; t<tc; t++) {
//         uint32_t n, k;
//         scanf("%d %d", &n, &k);
        
//         uint32_t *P = (uint32_t *)malloc(n * sizeof(uint32_t));
//         uint64_t *A = (uint64_t *)malloc(n * sizeof(uint64_t));
        
//         for (uint32_t i=0; i<n; i++) { scanf("%d", &P[i]); }
//         for (uint32_t i=0; i<n; i++) { scanf("%lld", &A[i]); }
        
//         printf("%lld\n", compute_min_radius(P, A, n, k));
        
//         free(P);
//         free(A);
//     }
//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>

// uint64_t compute_min_radius(uint32_t *P, int64_t *A, uint32_t n, uint32_t k) {
//     // Allocate array for scaled positions (each A[i] multiplied by 60)
//     int64_t *scaledA = malloc(n * sizeof(int64_t));
//     for (uint32_t i = 0; i < n; i++) { scaledA[i] = A[i] * 60LL; }

//     // Set up binary search for candidate q = 60*d.
//     uint64_t low = 0;
//     uint64_t high = 5 * (scaledA[n-1] - scaledA[0]) + 1;  // worst-case upper bound
//     uint64_t ans = high;

//     while (low <= high) {
//         uint64_t mid = (low + high) / 2;
//         // Greedy feasibility check: can we cover all cities with at most k towers using candidate mid?
//         uint32_t towersUsed = 0;
//         uint32_t i = 0;
//         while (i < n) {
//             int64_t cur = scaledA[i];  // leftmost city not yet covered
//             int64_t bestRight = -1;
//             uint32_t j = i;
//             // Try all potential towers that could cover city i.
//             while (j < n && (scaledA[j] - (mid * P[j] / 100)) <= cur) {
//                 int64_t right = scaledA[j] + (mid * P[j] / 100);
//                 if (right > bestRight) { bestRight = right; }
//                 j++;
//             }
//             // If no tower covers the current city, candidate mid fails.
//             if (bestRight < cur) {break;}
//             towersUsed++;
//             // Skip cities that are covered by the chosen tower.
//             while (i < n && scaledA[i] <= bestRight) { i++; }
//         }
//         // Candidate mid is feasible if all cities are covered and we used at most k towers.
//         if (i == n && towersUsed <= k) {
//             ans = mid;
//             if (mid == 0) break;  // Avoid underflow.
//             high = mid - 1;
//         } 
//         else { low = mid + 1; }
//     }
//     free(scaledA);
//     return ans;
// }

// int main() {
//     uint32_t tc;
//     scanf("%d", &tc);

//     for (uint32_t t = 0; t < tc; t++) {
//         uint32_t n, k;
//         scanf("%d %d", &n, &k);

//         uint32_t *P = malloc(n * sizeof(uint32_t));
//         int64_t *A = malloc(n * sizeof(int64_t));

//         for (uint32_t i = 0; i < n; i++) { scanf("%d", &P[i]); }
//         for (uint32_t i = 0; i < n; i++) { scanf("%lld", &A[i]); }

//         // Print the computed result (q = 60*d) using "%llu" for uint64_t.
//         printf("%llu\n", compute_min_radius(P, A, n, k));

//         free(P);
//         free(A);
//     }
//     return 0;
// }

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void place_towers(uint64_t *A, uint32_t n, uint32_t k) {
    if (k == n) return 0;
    uint64_t *towers = (uint64_t *)malloc(k * sizeof(uint64_t));
    for (uint32_t i = 0; i < k; i++) { towers[i] = A[i]; }

    // Step 2: Adjust towers to avoid overlap and ensure full coverage
    uint32_t lastCovered = 0;
    for (uint32_t i = 0; i < k; i++) {
        // Push the tower forward if possible while keeping coverage
        uint32_t newPos = lastCovered; 
        while (newPos<n && A[newPos] <= towers[i] + (A[n-1] - A[0]) / k) {
            newPos++;
        }
        if (newPos > lastCovered) {
            towers[i] = A[newPos - 1];
            lastCovered = newPos - 1;
        }
    }

    // Step 3: Print placed tower locations (for debugging)
    printf("Placed Towers at: ");
    for (uint32_t i = 0; i < k; i++) {
        printf("%llu ", towers[i]);
    }
    printf("\n");
    free(towers);
}

int main() {
    uint32_t n = 5, k = 2;
    uint64_t A[] = {1, 3, 5, 7, 9};
    place_towers(A, n, k);
    return 0;
}
