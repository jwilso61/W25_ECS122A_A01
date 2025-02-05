
def compute_diamter(n, edges):
    # Input: `n` - the size of the tree
    # `edges` - a list of pairs of integers denoting ends of edges of the tree
    # Output: An integer - the diameter of the tree
    diameter = 0
    # Write code to compute the diameter
    return diameter


T = int(input())
for _ in range(T):
    n = int(input())
    edges = []
    for e in range(n-1):
        u, v  = map(int, input().split(' '))
        edges.append((u, v))
    print(compute_diamter(n, edges))
