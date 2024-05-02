#include <iostream>
using namespace std;

const int MAX_N = 20;
int n, cost[MAX_N][MAX_N], assignment[MAX_N];
bool used[MAX_N];
int minCost = INT_MAX;

void branch_and_bound(int idx, int curr_cost) {
    if (idx == n) {
        minCost = min(minCost, curr_cost);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = true;
            assignment[idx] = i;
            branch_and_bound(idx + 1, curr_cost + cost[idx][i]);
            used[i] = false;
        }
    }
}

int main() {
    cout << "Enter the number of jobs: ";
    cin >> n;

    cout << "Enter the cost matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    branch_and_bound(0, 0);

    cout << "Minimum cost: " << minCost << "\n";
    cout << "Assignment:\n";
    for (int i = 0; i < n; i++) {
        cout << "Job " << i << " -> Person " << assignment[i] << "\n";
    }

    return 0;
}