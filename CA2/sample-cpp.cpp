#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v;
    Edge(){}
    Edge(int a, int b) { u = a; v = b; }
};


int compute_diameter(int n, vector<Edge> T) {
    // Please complete this function: given n and the edges of T, return the diameter of T
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    for (int t = 0; t < tc; t++) {
        int n;
        cin >> n;
        vector<Edge> T(n - 1);
        for (int i = 0; i < n - 1; i++) {
            cin >> T[i].u >> T[i].v;
        }
        int answer = compute_diameter(n, T);
        cout << answer << '\n';
    }
}
