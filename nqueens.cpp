#include <iostream>
#include <vector>

using namespace std;

bool isSafe(const vector<vector<int>>& board, int row, int col, int n) {
    // Check if there is a queen in the same column
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < n; --i, ++j) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

bool solveNQueensUtil(vector<vector<int>>& board, int row, int n) {
    if (row == n) {
        // All queens are successfully placed
        return true;
    }

    for (int col = 0; col < n; ++col) {
        if (isSafe(board, row, col, n)) {
            // Place the queen
            board[row][col] = 1;

            // Recur to place rest of the queens
            if (solveNQueensUtil(board, row + 1, n)) {
                return true;
            }

            // If placing queen in board[row][col] doesn't lead to a solution, backtrack
            board[row][col] = 0;
        }
    }

    // If no position is found to place this queen, return false
    return false;
}

void solveNQueens(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));

    if (solveNQueensUtil(board, 0, n)) {
        // Print the solution
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No solution exists." << endl;
    }
}

int main() {
    int n = 4; // Change n to solve for different board sizes
    solveNQueens(n);
    return 0;
}
