/*
 * ============================================================================
 * LEETCODE 2270: NUMBER OF WAYS TO SPLIT ARRAY
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Prefix Sum Logic: Tracking a running sum as we iterate.
 * - 64-bit Integers: Using `long long` to prevent integer overflow when 
 * adding many large numbers together.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Iterate through the array once to calculate the `totalSum`. Make 
 * sure to store this in a `long long`.
 * Step 2: Initialize `leftSum` and `validSplits` to 0.
 * Step 3: Iterate through the array again, stopping exactly one element 
 * before the end (a split requires at least one element on the right side).
 * Step 4: Add the current number to `leftSum`.
 * Step 5: Calculate `rightSum` on the fly by subtracting `leftSum` from 
 * `totalSum`.
 * Step 6: If `leftSum >= rightSum`, increment `validSplits`.
 * Step 7: Return `validSplits`.
 * ============================================================================
 */

#include <iostream>
#include <vector>

class Solution {
public:
    /**
     * @brief Calculates the number of valid splits where the left sum is >= right sum.
     * Complexity Analysis:
     * - Time: O(N). We iterate through the array twice (once for total, once for splits).
     * - Space: O(1). We only use three integer variables regardless of array size.
     */
    int waysToSplitArray(const std::vector<int>& nums) {
        
        // 64-bit integer to prevent overflow (Max sum can be 10^10)
        long long totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        long long leftSum = 0;
        int validSplits = 0;

        // Iterate until n - 1 because the right part must have at least one element
        for (size_t i = 0; i < nums.size() - 1; ++i) {
            leftSum += nums[i];
            
            // The right side is dynamically calculated
            long long rightSum = totalSum - leftSum;

            if (leftSum >= rightSum) {
                validSplits++;
            }
        }

        return validSplits;
    }
};

// Helper function to print results
void printResult(const std::vector<int>& nums, int expected) {
    Solution solver;
    int result = solver.waysToSplitArray(nums);
    
    std::cout << "Input: [";
    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";
    
    std::cout << "Expected: " << expected << " | Result: " << result;
    if (result == expected) {
        std::cout << " [PASS]\n\n";
    } else {
        std::cout << " [FAIL]\n\n";
    }
}

int main() {
    // Test Case 1: Standard case
    std::vector<int> nums1 = {10, 4, -8, 7};
    printResult(nums1, 2);

    // Test Case 2: Only two elements
    std::vector<int> nums2 = {2, 3, 1, 0};
    printResult(nums2, 2);

    // Test Case 3: Triggers Integer Overflow if using 'int'
    std::vector<int> nums3 = {100000, 100000, 100000, 100000};
    printResult(nums3, 3);

    return 0;
}
