/*
 * ============================================================================
 * LEETCODE 198: HOUSE ROBBER
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Dynamic Programming (DP): Breaking down a complex problem into simpler, 
 * overlapping subproblems.
 * - State Space Optimization: Recognizing that if a DP formula only relies on 
 * the last `k` values, you only need `k` variables, not an entire array of size N.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Handle the empty array edgecase.
 * Step 2: Initialize `rob1` (representing DP[i-2]) and `rob2` (representing DP[i-1]) to 0.
 * Step 3: Iterate through every house in `nums`.
 * Step 4: Calculate the max money if we rob the current house: `rob1 + n`.
 * Step 5: Calculate the max money if we skip the current house: `rob2`.
 * Step 6: The `current_max` is the `std::max` of those two choices.
 * Step 7: Slide the window forward: `rob1` becomes `rob2`, and `rob2` becomes `current_max`.
 * Step 8: When the loop finishes, `rob2` holds the global maximum.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - The Sliding Window of DP: Think of `rob1` and `rob2` as a 2-element window 
 * sliding across the array. You calculate the 3rd element, push the window forward, 
 * and forget the past. This perfectly reduces O(n) space to O(1) space.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm> // Required for std::max

class Solution {
public:
    /**
     * @brief Finds the maximum amount of money you can rob tonight without alerting the police.
     * Complexity Analysis:
     * - Time: O(n). We iterate through the array of houses exactly once.
     * - Space: O(1). We only use two integer variables instead of a full DP array.
     */
    int rob(std::vector<int>& nums) {
        if (nums.empty()) return 0;

        int rob1 = 0; // Represents DP[i-2]
        int rob2 = 0; // Represents DP[i-1]

        // [rob1, rob2, n, n+1, ...]
        for (int n : nums) {
            // Formula: DP[i] = max(DP[i-1], DP[i-2] + nums[i])
            int current_max = std::max(rob2, rob1 + n);
            
            // Shift variables forward for the next iteration
            rob1 = rob2;
            rob2 = current_max;
        }

        return rob2;
    }
};

// Helper function to print results
void printResult(std::vector<int> nums, int expected, int result) {
    std::cout << "Input: [";
    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";
    std::cout << "Expected Max Loot: " << expected << " | Result: " << result << "\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard alternating
    std::vector<int> nums1 = {1, 2, 3, 1};
    // Rob house 1 (money = 1) and then rob house 3 (money = 3). Total = 4.
    printResult(nums1, 4, solver.rob(nums1));

    // Test Case 2: Needing to skip two houses in a row to get a bigger payout
    std::vector<int> nums2 = {2, 7, 9, 3, 1};
    // Rob house 1 (2), house 3 (9), and house 5 (1). Total = 12.
    printResult(nums2, 12, solver.rob(nums2));

    // Test Case 3: A single huge house
    std::vector<int> nums3 = {2, 1, 1, 2};
    // Rob house 1 (2), skip two houses, rob house 4 (2). Total = 4.
    printResult(nums3, 4, solver.rob(nums3));

    return 0;
}
