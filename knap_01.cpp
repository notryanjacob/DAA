#include<iostream>
#include<numeric>
#include<vector>

using namespace std;

const int MAX_N = 20;
int n, W, weight[MAX_N], value[MAX_N];
int maxProfit = 0;
vector<int> selected;

void bound(int idx, int curr_weight, int curr_profit, int curr_bound) {
    if (curr_bound < maxProfit)
        return;

    if (idx == n) {
        if (curr_weight <= W && curr_profit > maxProfit) {
            maxProfit = curr_profit;
            selected.clear();
            for (int i = 0; i < n; i++) {
                if (weight[i] > 0 && curr_weight - weight[i] >= 0) {
                    selected.push_back(i);
                    curr_weight -= weight[i];
                }
            }
        }
        return;
    }

    bound(idx + 1, curr_weight, curr_profit, curr_bound);
    int new_bound = curr_bound - value[idx];
    if (new_bound >= maxProfit)
        bound(idx + 1, curr_weight + weight[idx], curr_profit + value[idx], new_bound);
}

int main() {
    // Dummy data
    n = 5;
    W = 10;
    weight[0] = 5; value[0] = 10;
    weight[1] = 4; value[1] = 8;
    weight[2] = 3; value[2] = 6;
    weight[3] = 2; value[3] = 5;
    weight[4] = 1; value[4] = 2;

    bound(0, 0, 0, accumulate(value, value + n, 0));

    cout << "Maximum profit: " << maxProfit << "\n";
    cout << "Selected items: ";
    for (int i : selected) {
        cout << i << " ";
    }
    cout << "\n";

    return 0;
}