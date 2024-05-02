#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int matrixChainMultiplication(const vector<int>& dimensions, const vector<int>& order, vector<vector<int>>& dp, vector<vector<int>>& splitPoints) {
    int n = dimensions.size() - 1; // Number of matrices

    // Fill the dp table using bottom-up dynamic programming
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + dimensions[i] * dimensions[k + 1] * dimensions[j + 1];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    splitPoints[i][j] = k; // Store the split point for reconstruction
                }
            }
        }
    }

    return dp[0][n - 1];
}

void printOptimalParentheses(const vector<vector<int>>& splitPoints, int i, int j) {
    if (i == j) {
        cout << "A" << i + 1;
    } else {
        cout << "(";
        printOptimalParentheses(splitPoints, i, splitPoints[i][j]);
        printOptimalParentheses(splitPoints, splitPoints[i][j] + 1, j);
        cout << ")";
    }
}

int main() {
    // Fixed input dimensions
    vector<int> dimensions = {3, 2, 4, 2, 5};

    int n = dimensions.size() - 1; // Number of matrices

    // Input: Order of matrices A1, A2, A3, A4
    vector<int> order(n);
    cout << "Enter the order of matrices A1, A2, A3, A4:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Order of A" << i + 1 << ": ";
        cin >> order[i];
    }

    // Initialize dp table and split points vector
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> splitPoints(n, vector<int>(n, 0));

    // Compute minimum cost and store split points
    int minCost = matrixChainMultiplication(dimensions, order, dp, splitPoints);

    // Output the optimal solution
    cout << "Optimal Parenthesization: ";
    printOptimalParentheses(splitPoints, 0, n - 1);
    cout << endl;
    cout << "Minimum Cost: " << minCost << endl;

    return 0;
}
