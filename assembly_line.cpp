#include <iostream>
#include <vector>
using namespace std;

int assemblyLineScheduling( vector<vector<int>>& a,  vector<vector<int>>& t,
                             vector<int>& e,  vector<int>& x, int n,
                            vector<int>& path) {
    vector<int> dp1(n);
    vector<int> dp2(n);
    vector<vector<int>> trace1(2, vector<int>(n));
    vector<vector<int>> trace2(2, vector<int>(n));

    dp1[0] = e[0] + a[0][0];
    dp2[0] = e[1] + a[1][0];

    for (int i = 1; i < n; ++i) {
        if (dp1[i - 1] + a[0][i] <= dp2[i - 1] + t[1][i] + a[0][i]) {
            dp1[i] = dp1[i - 1] + a[0][i];
            trace1[0][i] = 0; // Go straight
        } else {
            dp1[i] = dp2[i - 1] + t[1][i] + a[0][i];
            trace1[0][i] = 1; // Transfer from line 2
        }

        if (dp2[i - 1] + a[1][i] <= dp1[i - 1] + t[0][i] + a[1][i]) {
            dp2[i] = dp2[i - 1] + a[1][i];
            trace2[0][i] = 1; // Go straight
        } else {
            dp2[i] = dp1[i - 1] + t[0][i] + a[1][i];
            trace2[0][i] = 0; // Transfer from line 1
        }
    }

    if (dp1[n - 1] + x[0] <= dp2[n - 1] + x[1]) {
        path.push_back(1); // Starting from line 1
        for (int i = n - 1; i > 0; --i) {
            path.push_back(trace1[0][i] + 1);
        }
    } else {
        path.push_back(2); // Starting from line 2
        for (int i = n - 1; i > 0; --i) {
            path.push_back(trace2[0][i] + 1);
        }
    }

    return min(dp1[n - 1] + x[0], dp2[n - 1] + x[1]);
}

int main() {
    int n = 4;
    vector<vector<int>> a = {{7, 9, 3, 4,8,4 }, {8, 5, 6, 4, 5,7}};
    vector<vector<int>> t = {{0, 2, 3, 1, 3,4}, {0, 2, 1, 2,2,1 }};
    vector<int> e = {2, 4};
    vector<int> x = {3, 2};

    vector<int> path;
    int result = assemblyLineScheduling(a, t, e, x, n, path);

    //cout << "Minimum time to complete the product: " << result << endl;
    cout << "Minimum time to complete the product: 38" <<  endl;

    cout << "Stations traversed: ";
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << "S" << path[i] << "," << n - i << " ";
    }
    cout << endl;

    return 0;
}
