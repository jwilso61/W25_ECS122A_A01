# def compute_min_radius(P, A, k):
#     # Your code here. Return the minimum possible d times 60 
#     pass

# tc = int(input())
# results = []
# for _ in range(tc):
#     n, k = map(int, input().split())
#     P = list(map(int, input().split()))
#     A = list(map(int, input().split()))
#     print(compute_min_radius(P, A, k))

def can_cover(A, k, q):
    """ Check if all cities can be covered with `k` towers and radius `q` (scaled d). """
    towers_used = 0
    i = 0
    n = len(A)
    
    while i < n:
        towers_used += 1
        if towers_used > k:
            return False  # Exceeded allowed towers

        # Place tower at A[i] and determine max coverage
        coverage_end = A[i] + q

        # Move i forward to the next uncovered city
        while i < n and A[i] <= coverage_end:
            i += 1
    
    return towers_used <= k

def compute_min_radius(P, A, k):
    """ Binary search to find the minimum q = 60 * d """
    n = len(A)
    
    # Scale city positions by 60
    A = [x * 60 for x in A]

    # If we have enough towers, no range is needed
    if k >= n:
        return 0  

    low, high = 0, A[-1] - A[0]
    ans = high

    while low <= high:
        mid = (low + high) // 2

        if can_cover(A, k, mid):
            ans = mid
            high = mid - 1
        else:
            low = mid + 1

    return ans  # q = 60 * d

# Read input and execute
tc = int(input())
results = []
for _ in range(tc):
    n, k = map(int, input().split())
    P = list(map(int, input().split()))  # Ignored, since all p_i = 100
    A = list(map(int, input().split()))
    print(compute_min_radius(P, A, k))
