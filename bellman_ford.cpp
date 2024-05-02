#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Edge {
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

const int INF = numeric_limits<int>::max();

void bellmanFord(int n, int source, vector<Edge> edges, vector<int>& dist) {
    dist.assign(n, INF);
    dist[source] = 0;

    for (int i = 0; i < n - 1; i++) {
        bool relaxed = false;
        for (const Edge& e : edges) {
            if (dist[e.src] != INF && dist[e.dest] > dist[e.src] + e.weight) {
                dist[e.dest] = dist[e.src] + e.weight;
                relaxed = true;
            }
        }
        if (!relaxed) break;
    }

    // Check for negative-weight cycles
    for (const Edge& e : edges) {
        if (dist[e.src] != INF && dist[e.dest] > dist[e.src] + e.weight) {
            cout << "Negative-weight cycle detected!" << endl;
            return;
        }
    }

    // Print the shortest distances
    for (int i = 0; i < n; i++) {
        cout << "Shortest distance from " << source << " to " << i << " is " << dist[i] << endl;
    }
}

int main() {
    int n = 5;  // Number of vertices
    int source = 0;  // Source vertex

    // Edges in the graph
    vector<Edge> edges = {
        Edge(0, 1, -1),
        Edge(0, 2, 4),
        Edge(1, 2, 3),
        Edge(1, 3, 2),
        Edge(1, 4, 2),
        Edge(3, 2, 5),
        Edge(3, 1, 1),
        Edge(4, 3, -3)
    };

    vector<int> dist;
    bellmanFord(n, source, edges, dist);

    return 0;
}