#include<iostream>
#include<queue>

using namespace std;

#define V 6

bool bfs(int rgraph[V][V], int s, int t, int parent[]) {
    vector<int> vis(V, 0);
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++) {
            if (vis[v] == 0 && rgraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                vis[v] = 1;
                parent[v] = u;
            }
        }
    }

    return false;
}

int ford_fulk(int graph[V][V], int s, int t) {
    int u, v;
    int rgraph[V][V];
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            rgraph[u][v] = graph[u][v];
        }
    }

    int parent[V];
    int max_flow = 0;
    while (bfs(rgraph, s, t, parent)) {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rgraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rgraph[u][v] -= path_flow;
            rgraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    int s = 0;
    int t = 5;

    int max_flow = ford_fulk(graph, s, t);
    cout << "The maximum flow is: " << max_flow << endl;
    return 0;
}