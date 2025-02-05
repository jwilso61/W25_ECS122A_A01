#include <iostream>
#include <vector>
#include <queue>
#include <limits>

typedef std::pair<int, int> Pair; // Define a pair to represent a (cost, node)

void dijkstra(int start, const std::vector<std::vector<Pair>>& graph) {
    int n = graph.size();  // Number of nodes

    // Initialize distance to all nodes as infinity
    std::vector<int> distance(n, std::numeric_limits<int>::max());
    distance[start] = 0;  // Distance to start node is 0

    // Min-heap (priority queue) to pick the node with the smallest distance
    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> min_heap;
    min_heap.push({0, start});  // Start with the source node

    std::cout << "Starting Dijkstra's Algorithm from node " << start << ".\n\n";

    while (!min_heap.empty()) {
        int current_distance = min_heap.top().first;
        int current_node = min_heap.top().second;
        min_heap.pop();

        std::cout << "Visiting node " << current_node << " with current distance " << current_distance << ".\n";

        // Skip if the distance is not optimal (already found a shorter path)
        if (current_distance > distance[current_node]) {
            std::cout << "Skipping node " << current_node << " as a shorter path was already found.\n\n";
            continue;
        }

        // Explore neighbors
        for (const Pair& neighbor : graph[current_node]) {
            int next_node = neighbor.second;
            int edge_weight = neighbor.first;

            std::cout << "  Exploring edge to node " << next_node << " with weight " << edge_weight << ".\n";

            // Check if a shorter path to next_node exists
            if (distance[current_node] + edge_weight < distance[next_node]) {
                std::cout << "  Found a shorter path to node " << next_node << ": "
                          << distance[current_node] + edge_weight << " (previous: " << distance[next_node] << ").\n";
                distance[next_node] = distance[current_node] + edge_weight;
                min_heap.push({distance[next_node], next_node});
            } else {
                std::cout << "  No shorter path to node " << next_node << " found.\n";
            }
        }
        std::cout << "\n";
    }

    // Output the shortest distances
    std::cout << "Final shortest distances from node " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        if (distance[i] == std::numeric_limits<int>::max()) {
            std::cout << "Node " << i << ": Unreachable\n";
        } else {
            std::cout << "Node " << i << ": " << distance[i] << "\n";
        }
    }
}

int main() {
    int n = 6;  // Number of nodes
    std::vector<std::vector<Pair>> graph(n);

    // Add edges (weight, destination)
    graph[0].push_back({4, 5});
    graph[0].push_back({5, 4});
    graph[0].push_back({2, 2});
    graph[1].push_back({3, 5});
    graph[1].push_back({2, 4});
    graph[2].push_back({2, 0});
    graph[2].push_back({1, 4});
    graph[2].push_back({4, 3});
    graph[3].push_back({4, 3});
    graph[4].push_back({2, 1});
    graph[4].push_back({1, 5});
    graph[4].push_back({5, 0});
    graph[4].push_back({1, 2});
    graph[5].push_back({3, 1});
    graph[5].push_back({1, 4});
    graph[5].push_back({4, 0});

    int start_node = 0;
    dijkstra(start_node, graph);

    return 0;
}
