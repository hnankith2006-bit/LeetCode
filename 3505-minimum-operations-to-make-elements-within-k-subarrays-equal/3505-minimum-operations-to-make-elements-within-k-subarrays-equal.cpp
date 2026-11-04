#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        vector<long long> minOps; 
        
        multiset<long long> lower, upper;
        long long lowerSum = 0, upperSum = 0;
        
        for (int i = 0; i < n; ++i) {
            // 1. Add the incoming element
            if (lower.empty() || nums[i] <= *lower.rbegin()) {
                lower.insert(nums[i]);
                lowerSum += nums[i];
            } else {
                upper.insert(nums[i]);
                upperSum += nums[i];
            }
            
            // 2. Remove the outgoing element that slid out of the window
            if (i >= x) {
                long long outNum = nums[i - x];
                auto it = lower.find(outNum);
                if (it != lower.end()) {
                    lower.erase(it);
                    lowerSum -= outNum;
                } else {
                    upper.erase(upper.find(outNum));
                    upperSum -= outNum;
                }
            }
            
            // 3. Balance the two multisets
            while (lower.size() < upper.size()) {
                long long val = *upper.begin();
                upper.erase(upper.begin());
                upperSum -= val;
                lower.insert(val);
                lowerSum += val;
            }
            while (lower.size() > upper.size() + 1) {
                auto it = lower.end();
                --it;
                long long val = *it;
                lower.erase(it);
                lowerSum -= val;
                upper.insert(val);
                upperSum += val;
            }
            
            // 4. Calculate total operations needed for the current valid window
            if (i >= x - 1) {
                long long median = *lower.rbegin();
                long long ops = (median * lower.size() - lowerSum) + (upperSum - median * upper.size());
                minOps.push_back(ops);
            }
        }
        
        // 5. DP to find k non-overlapping windows minimizing the operations sum
        int m = minOps.size();
        const long long INF = 1e18;
        
        // Size is m + x + 1 to safely accommodate the i + x jump without bounds checking
        vector<vector<long long>> dp(m + x + 1, vector<long long>(k + 1, INF));
        
        for (int i = 0; i <= m + x; ++i) {
            dp[i][0] = 0;
        }
        
        for (int i = m - 1; i >= 0; --i) {
            for (int j = 1; j <= k; ++j) {
                // Minimum of skipping the current index or picking the subarray starting here
                dp[i][j] = min(dp[i + 1][j], minOps[i] + dp[i + x][j - 1]);
            }
        }
        
        return dp[0][k];
    }
};