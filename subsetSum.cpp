#include <iostream>
#include <vector>

using namespace std;

bool subsetSum(const vector<int>& nums, int target, vector<int>& subset) {
    int n = nums.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // Base case: If the target sum is 0, then there's always an empty subset.
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = true;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= target; ++j) {
            if (j < nums[i - 1]) {
                // If the current element is greater than the target sum, exclude it.
                dp[i][j] = dp[i - 1][j];
            } else {
                // Check if it's possible to achieve the target sum with or without including the current element.
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
            }
        }
    }

    // If it's possible to achieve the target sum, reconstruct the subset.
    if (dp[n][target]) {
        int i = n, j = target;
        while (i > 0 && j > 0) {
            if (dp[i - 1][j]) {
                // Element not included in the subset.
                --i;
            } else {
                // Element included in the subset.
                subset.push_back(nums[i - 1]);
                j -= nums[i - 1];
                --i;
            }
        }
        return true;
    }

    return false;
}

int main() {
    vector<int> nums = {5,10,12,13,15,18};
    int target = 30;
    vector<int> subset;

    if (subsetSum(nums, target, subset)) {
        cout << "Subset that sums up to " << target << ": ";
        for (int i = 0; i < subset.size(); ++i) {
            cout << subset[i] << " ";
        }
        cout << endl;
    } else {
        cout << "No subset sums up to " << target << "." << endl;
    }

    return 0;
}
