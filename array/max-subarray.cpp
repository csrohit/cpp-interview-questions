/*
 * ============================================================================
 * LEETCODE 53: MAXIMUM SUBARRAY (KADANE'S ALGORITHM)
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Subarrays vs Subsequences: A subarray must be strictly contiguous 
 * (unbroken elements side-by-side). A subsequence can skip elements.
 * - Kadane's Algorithm: A greedy/dynamic programming hybrid that calculates 
 * the maximum subarray ending at a specific position.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Initialize `currentSum` and `maxSum` to the very first element in 
 * the array (`nums[0]`). Do NOT initialize them to 0, because if the array 
 * contains only negative numbers (e.g., [-3, -5, -2]), initializing to 0 
 * would incorrectly return 0.
 * Step 2: Iterate through the array starting from index 1.
 * Step 3: At each step, update `currentSum` to be the maximum of either:
 * a) The current element standing alone (`nums[i]`)
 * b) The current element added to the previous sum (`currentSum + nums[i]`)
 * Step 4: After updating `currentSum`, check if it is strictly greater than 
 * our global record `maxSum`. If it is, update `maxSum`.
 * Step 5: Return `maxSum`.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Dead Weight Rule: Notice that `max(nums[i], currentSum + nums[i])` is 
 * functionally identical to asking: "Is currentSum negative?". If currentSum 
 * is negative, `currentSum + nums[i]` will ALWAYS be smaller than `nums[i]` 
 * alone. Kadane's algorithm systematically sheds negative dead weight.
 * - 1D DP Optimization: This is actually a Dynamic Programming problem! The 
 * true DP array would store the max sum ending at each index. But because 
 * we only ever need to look at the immediate previous state (`currentSum`), 
 * we don't need a full array. We optimize O(n) space down to O(1) space.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm> // Required for std::max

class Solution {
public:
    /**
     * @brief Finds the contiguous subarray with the largest sum.
     * Complexity Analysis:
     * - Time: O(n). We iterate through the array exactly once.
     * - Space: O(1). We only use two integer variables to track state.
     */
    int maxSubArray(std::vector<int>& nums) {
        if (nums.empty()) return 0;

        // Initialize to the first element
        int currentSum = nums[0];
        int maxSum = nums[0];

        // Iterate starting from the second element
        for (int i = 1; i < nums.size(); ++i) {
            
            // The core of Kadane's Algorithm
            // Do we extend the previous subarray, or start a new one?
            currentSum = std::max(nums[i], currentSum + nums[i]);

            // Track the maximum value we've ever seen
            maxSum = std::max(maxSum, currentSum);
        }

        return maxSum;
    }
};

// Helper function to print results
void printResult(std::vector<int> nums, int expected, int result) {
    std::cout << "Input Array: [";
    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";
    std::cout << "Expected Max Sum: " << expected << " | Result: " << result << "\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard case with mixed positive and negative numbers
    std::vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    // The maximum subarray is [4, -1, 2, 1] which sums to 6.
    printResult(nums1, 6, solver.maxSubArray(nums1));

    // Test Case 2: Array with a single positive number
    std::vector<int> nums2 = {1};
    printResult(nums2, 1, solver.maxSubArray(nums2));

    // Test Case 3: Array with ALL positive numbers
    std::vector<int> nums3 = {5, 4, 1, 7, 8};
    // If all are positive, Kadane's will just add them all up.
    printResult(nums3, 25, solver.maxSubArray(nums3));

    // Test Case 4: Array with ALL negative numbers
    std::vector<int> nums4 = {-5, -2, -9, -1};
    // The "max" sum is the least negative single number (-1).
    // This perfectly illustrates why we must initialize to nums[0] instead of 0.
    printResult(nums4, -1, solver.maxSubArray(nums4));

    return 0;
}
