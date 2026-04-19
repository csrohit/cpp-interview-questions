/*
 * ============================================================================
 * LEETCODE 16: 3SUM CLOSEST
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - 3Sum (LeetCode 15): The core Anchor + Two-Pointer architecture.
 * - Absolute Difference: Using `std::abs()` to measure "distance" between two 
 * numbers on a number line.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Sort the array.
 * Step 2: Initialize `closestSum` with the sum of the first three elements. 
 * This gives us a valid baseline to compare against.
 * Step 3: Iterate through the array using an anchor pointer `i` up to `n - 2`.
 * Step 4: Initialize Pointers: Set `left = i + 1` and `right = n - 1`.
 * Step 5: Squeeze: While `left < right`, calculate the `currentSum`.
 * Step 6: The Exact Match Check: If `currentSum == target`, return it immediately 
 * (difference is 0, impossible to get closer).
 * Step 7: The State Tracker: If `abs(target - currentSum) < abs(target - closestSum)`, 
 * overwrite `closestSum` with `currentSum`.
 * Step 8: Move pointers: If `currentSum < target`, increment `left`. If 
 * `currentSum > target`, decrement `right`.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - State Tracking over Exact Matching: Many interview problems will ask you to 
 * find the "best" or "closest" option rather than an exact match. This pattern 
 * requires initializing a tracking variable with a valid baseline (not just 0 or 
 * INT_MAX, which can cause overflow or logic errors) and updating it whenever 
 * you find a better state.
 * - No Deduplication Required (Mostly): Because we just want the closest sum, 
 * evaluating duplicate combinations doesn't hurt the final answer. However, 
 * skipping duplicate anchors is still a good optimization for speed.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> // Required for std::abs

class Solution {
public:
    /**
     * @brief Finds the triplet sum that is closest to the target.
     * Complexity Analysis:
     * - Time: O(n^2). Sorting takes O(n log n). The outer loop runs n times, and 
     * the inner two-pointer sweep takes O(n).
     * - Space: O(1) or O(n) depending on the sorting algorithm implementation.
     */
    int threeSumClosest(std::vector<int>& nums, int target) {
        int n = nums.size();
        
        // Step 1: Sort the array
        std::sort(nums.begin(), nums.end());
        
        // Step 2: Initialize with a valid baseline sum
        int closestSum = nums[0] + nums[1] + nums[2];

        // Step 3: Iterate with an anchor
        for (int i = 0; i < n - 2; ++i) {
            
            // Optimization: Skip duplicate anchors to save time
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            // Step 4: Initialize pointers
            int left = i + 1;
            int right = n - 1;

            // Step 5: Squeeze
            while (left < right) {
                int currentSum = nums[i] + nums[left] + nums[right];

                // Step 6: Exact match check (best possible scenario)
                if (currentSum == target) {
                    return currentSum;
                }

                // Step 7: Update closest sum if we found a better one
                if (std::abs(target - currentSum) < std::abs(target - closestSum)) {
                    closestSum = currentSum;
                }

                // Step 8: Adjust pointers
                if (currentSum < target) {
                    left++; // Need more weight to get closer to target
                } else {
                    right--; // Need less weight to get closer to target
                }
            }
        }

        return closestSum;
    }
};

// Helper function to print results
void printResult(std::vector<int> nums, int target, int expected, int result) {
    std::cout << "Input: [";
    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "");
    }
    std::cout << "], Target: " << target << "\n";
    std::cout << "Expected: " << expected << " | Result: " << result << "\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard case
    std::vector<int> nums1 = {-1, 2, 1, -4};
    int target1 = 1;
    // Sorted: [-4, -1, 1, 2]. Closest sum: -1 + 1 + 2 = 2.
    printResult(nums1, target1, 2, solver.threeSumClosest(nums1, target1));

    // Test Case 2: Exact match exists
    std::vector<int> nums2 = {0, 0, 0};
    int target2 = 1;
    // Closest sum: 0 + 0 + 0 = 0.
    printResult(nums2, target2, 0, solver.threeSumClosest(nums2, target2));

    // Test Case 3: Multiple elements, closest is negative
    std::vector<int> nums3 = {4, 0, 5, -5, 3, 3, 0, -4, -5};
    int target3 = -2;
    // -5 + 0 + 3 = -2
    printResult(nums3, target3, -2, solver.threeSumClosest(nums3, target3));

    return 0;
}
