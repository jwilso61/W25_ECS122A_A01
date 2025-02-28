#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int can_cover(uint64_t q, uint64_t *A, uint32_t n, uint32_t k) {
    uint32_t towersUsed = 0, i = 0;
    while (i < n) {
        towersUsed++;
        if (towersUsed > k) return 0; 
        uint64_t coverage_end = A[i] + q; 
        while (i<n && A[i] <= coverage_end) i++; 
    }
    return towersUsed <= k;
}

uint64_t compute_min_q(uint64_t *A, uint32_t n, uint32_t k) {
    if (k >= n) return 0;
    uint64_t low = 0, high = A[n-1] - A[0], ans = high;
    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;
        if (can_cover(mid, A, n, k)) {
            ans = mid;
            high = mid - 1;
        } 
        else { low = mid + 1; }
    }
    return ans;
}

int main() {
    uint32_t tc;
    scanf("%d", &tc);

    for (uint32_t t = 0; t < tc; t++) {
        uint32_t n, k;
        scanf("%d %d", &n, &k);

        uint64_t *A = (uint64_t *)malloc(n * sizeof(uint64_t));
        uint32_t temp;
        for (uint32_t i = 0; i < n; i++) { scanf("%d", &temp); } 
        for (uint32_t i = 0; i < n; i++) { scanf("%lld", &A[i]); A[i] *= 60; } // Scale A[i] by 60

        printf("%lld\n", compute_min_q(A, n, k));

        free(A);
    }
    return 0;
}
