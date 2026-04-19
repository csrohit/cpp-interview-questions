/*
 * ============================================================================
 * LEETCODE 15: 3SUM
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Sorting Algorithms & Time Complexity: Must know that sorting takes O(n log n).
 * - Two Sum (LeetCode 1): Understanding how to combine numbers to hit a target.
 * - Two Sum II - Sorted Array (LeetCode 167): The core mechanic of this problem. 
 * You must understand the "Left-Right Pointer Squeeze" before adding the 
 * third "anchor" pointer.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Sort the array. This is mandatory for the two-pointer technique and 
 * for easily skipping duplicates.
 * Step 2: Iterate through the array using an anchor pointer `i` up to `n - 2`.
 * Step 3: Early Exit: If the anchor is > 0, break the loop (since the array 
 * is sorted, no subsequent numbers can bring the sum back down to 0).
 * Step 4: Skip Anchor Duplicates: If nums[i] == nums[i-1], `continue`.
 * Step 5: Initialize Pointers: Set `left = i + 1` and `right = n - 1`.
 * Step 6: Squeeze: While `left < right`, calculate the sum. Adjust `left` or 
 * `right` based on whether the sum is less than or greater than 0.
 * Step 7: Record and Deduplicate: If sum is 0, save the triplet, then advance 
 * both `left` and `right` past any identical consecutive numbers.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Sorting Organizes Chaos: Sorting transforms an O(n^3) brute-force problem 
 * into an O(n^2) structured search. It allows us to easily skip duplicate 
 * combinations without using a computationally expensive and messy Hash Set.
 * - Problem Reduction (N-Sum): To solve 3Sum, we "fix" one number (the anchor) 
 * and reduce the rest of the problem into a standard "2Sum II" problem.
 * - The Two-Pointer Squeeze: When searching for sums in a sorted array, using 
 * opposite-end pointers allows you to intelligently discard impossible 
 * combinations (Sum < Target -> move left; Sum > Target -> move right).
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief Solution for LeetCode 15: 3Sum.
 * * Pattern: Sorting + Two Pointers.
 * By sorting the array first, we reduce the 3Sum problem into a series of 
 * Two-Pointer sweeps, avoiding the massive overhead of deduplicating hash sets.
 */
class Solution {
public:
    /**
     * @brief Finds all unique triplets that sum to zero.
     * Complexity Analysis:
     * - Time: O(n^2). Sorting takes O(n log n). The outer loop runs n times, and 
     * the inner two-pointer sweep takes O(n). Total is O(n^2).
     * - Space: O(1) or O(n) depending on the sorting algorithm implementation.
     */
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        
        // Step 1: Sort the array to enable two-pointers and easy deduplication.
        std::sort(nums.begin(), nums.end());
        int n = nums.size();

        // Step 2: Iterate through the array. 
        // We stop at n - 2 because we need at least 3 elements to form a triplet.
        for (int i = 0; i < n - 2; ++i) {
            
            // EARLY STOP OPTIMIZATION: 
            // Since the array is sorted, if our smallest number (the anchor) 
            // is greater than 0, it's mathematically impossible to sum to 0.
            if (nums[i] > 0) break;

            // SKIP DUPLICATES for the anchor 'i'
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            // Step 3: Two Pointers Sweep
            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum < 0) {
                    left++; // Sum too small, need a larger number
                } 
                else if (sum > 0) {
                    right--; // Sum too big, need a smaller number
                } 
                else {
                    // We found a valid triplet!
                    result.push_back({nums[i], nums[left], nums[right]});

                    // SKIP DUPLICATES for the 'left' pointer
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    // SKIP DUPLICATES for the 'right' pointer
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }

                    // Move both pointers inward to look for new combinations
                    left++;
                    right--;
                }
            }
        }

        return result;
    }
};

// Helper function to print the result matrix
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    std::cout << "[";
    for (size_t i = 0; i < matrix.size(); ++i) {
        std::cout << "[";
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j] << (j < matrix[i].size() - 1 ? "," : "");
        }
        std::cout << "]" << (i < matrix.size() - 1 ? "," : "");
    }
    std::cout << "]\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard case with duplicates
    std::vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    std::cout << "Input: [-1, 0, 1, 2, -1, -4]\nResult: ";
    printMatrix(solver.threeSum(nums1));
    std::cout << "Expected: [[-1,-1,2],[-1,0,1]]\n\n";

    // Test Case 2: All zeros
    std::vector<int> nums2 = {0, 0, 0, 0};
    std::cout << "Input: [0, 0, 0, 0]\nResult: ";
    printMatrix(solver.threeSum(nums2));
    std::cout << "Expected: [[0,0,0]]\n\n";

    // Test Case 3: Impossible to make zero
    std::vector<int> nums3 = {0, 1, 1};
    std::cout << "Input: [0, 1, 1]\nResult: ";
    printMatrix(solver.threeSum(nums3));
    std::cout << "Expected: []\n";

    return 0;
}
