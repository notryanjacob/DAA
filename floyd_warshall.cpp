#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

void floydWarshall(vector<vector<int>>& dist, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int n = 4;  // Number of vertices

    // Adjacency matrix representing the weighted graph
    vector<vector<int>> graph = {
        {0, 5, INF, 8},
        {INF, 0, 1, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };

    vector<vector<int>> dist = graph;

    floydWarshall(dist, n);

    // Print the shortest distances between all pairs
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Shortest distance from " << i << " to " << j << " is " << dist[i][j] << endl;
        }
    }

    return 0;
}