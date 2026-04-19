/*
 * ============================================================================
 * LEETCODE 259: 3SUM SMALLER
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Two Sum II (LeetCode 167): The baseline Two-Pointer squeeze.
 * - 3Sum (LeetCode 15): Understanding the Anchor + Two-Pointer architecture.
 * - Combinatorics Trick: Understanding that in a sorted array, if an element 
 * at index `R` satisfies a `< target` condition with index `L`, all elements 
 * between `L` and `R` will also satisfy it.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Sort the array. This unlocks the mathematical guarantees needed to 
 * skip counting elements one by one.
 * Step 2: Initialize a `count` variable to 0.
 * Step 3: Iterate through the array using an anchor pointer `i` up to `n - 2`.
 * Step 4: Initialize Pointers: Set `left = i + 1` and `right = n - 1`.
 * Step 5: Squeeze: While `left < right`, calculate the sum.
 * Step 6: The "Aha!" Condition: If `sum < target`, it means `nums[right]` is 
 * small enough. Therefore, all numbers between `left` and `right` are 
 * also small enough. Add `(right - left)` to `count`, then increment `left`.
 * Step 7: If `sum >= target`, the sum is too big. Decrement `right` to reduce it.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Bulk Counting over Iteration: When you have a sorted array and an inequality 
 * (like < or >), you almost never need to count items one by one. You can use 
 * index math (`right - left`) to count entire valid ranges in O(1) time.
 * - No Deduplication Needed: Unlike standard 3Sum, this problem asks for the 
 * number of valid *index* triplets, not unique number combinations. Therefore, 
 * we do not need to write `while` loops to skip duplicate numbers.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    /**
     * @brief Finds the number of index triplets where the sum is less than target.
     * Complexity Analysis:
     * - Time: O(n^2). Sorting takes O(n log n). The outer loop runs n times, and 
     * the inner two-pointer sweep takes O(n). Total is O(n^2).
     * - Space: O(1) or O(n) depending on the sorting algorithm implementation.
     */
    int threeSumSmaller(std::vector<int>& nums, int target) {
        // Handle edge case where array has fewer than 3 elements
        int n = nums.size();
        if (n < 3) return 0;
        
        // Step 1: Sort the array
        std::sort(nums.begin(), nums.end());
        
        int count = 0;

        // Step 3: Iterate with an anchor
        for (int i = 0; i < n - 2; ++i) {
            
            // Step 4: Initialize pointers
            int left = i + 1;
            int right = n - 1;

            // Step 5: Squeeze
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum < target) {
                    // Step 6: The Bulk Counting Trick
                    // Since nums[right] works, everything from left+1 to right works too.
                    count += (right - left);
                    
                    // Move left up to check the next base pair
                    left++;
                } else {
                    // Step 7: Sum is too large or equal to target, shrink the right side
                    right--;
                }
            }
        }

        return count;
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
    std::vector<int> nums1 = {-2, 0, 1, 3};
    int target1 = 2;
    // Valid triplets: [-2, 0, 1] = -1 < 2  |  [-2, 0, 3] = 1 < 2
    printResult(nums1, target1, 2, solver.threeSumSmaller(nums1, target1));

    // Test Case 2: Empty array
    std::vector<int> nums2 = {};
    int target2 = 0;
    printResult(nums2, target2, 0, solver.threeSumSmaller(nums2, target2));

    // Test Case 3: No valid triplets
    std::vector<int> nums3 = {0, 0, 0};
    int target3 = 0;
    printResult(nums3, target3, 0, solver.threeSumSmaller(nums3, target3));

    return 0;
}
