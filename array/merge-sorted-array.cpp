/*
 * ============================================================================
 * LEETCODE 88: MERGE SORTED ARRAY
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Two Pointers: Using multiple indices to traverse arrays simultaneously.
 * - In-place Array Manipulation: Modifying an array without allocating 
 * additional space, keeping Space Complexity at O(1).
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Initialize three pointers: `p1` at the end of the valid numbers in 
 * `nums1` (m - 1), `p2` at the end of `nums2` (n - 1), and `p` at the very 
 * end of `nums1` (m + n - 1).
 * Step 2: Loop while both `p1` and `p2` are >= 0. Compare the values at `p1` 
 * and `p2`.
 * Step 3: Place the LARGER of the two values at position `p`.
 * Step 4: Decrement `p` and the pointer you just took the value from (`p1` or `p2`).
 * Step 5: Once the main loop finishes, it's possible `nums2` still has elements 
 * remaining (e.g., if `nums2` had all the smallest elements). Run a second 
 * loop to copy any remaining elements from `nums2` into `nums1`.
 * Step 6: (Note: We do not need a loop for leftover `nums1` elements because 
 * they are already resting in their correct sorted positions inside `nums1`!)
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Reverse Traversal Trick: When a problem asks you to merge or manipulate 
 * an array "in-place" and there is empty space at the end, almost always 
 * start your pointers from the BACK. This guarantees you will never overwrite 
 * data you haven't processed yet.
 * - Handle Leftovers Smartly: Always consider what happens when one array 
 * finishes before the other. In this specific problem, if `nums1` finishes 
 * first, we must copy the rest of `nums2`. If `nums2` finishes first, we do 
 * nothing, which saves execution time!
 * ============================================================================
 */

#include <iostream>
#include <vector>

/**
 * @brief Solution for LeetCode 88: Merge Sorted Array.
 * * Pattern: Two Pointers (Reverse Traversal).
 * By merging from the back to the front, we utilize the empty space at the 
 * end of nums1 to achieve O(1) space complexity without overwriting data.
 */
class Solution {
public:
    /**
     * @brief Merges nums2 into nums1 as one sorted array in-place.
     * Complexity Analysis:
     * - Time: O(m + n). We traverse the elements of both arrays exactly once.
     * - Space: O(1). We are modifying nums1 in-place.
     */
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        // Initialize pointers
        int p1 = m - 1;           // Last real element in nums1
        int p2 = n - 1;           // Last element in nums2
        int p = m + n - 1;        // Last position of the merged array in nums1

        // Step 1 & 2: Compare from the back and place the largest element at 'p'
        while (p1 >= 0 && p2 >= 0) {
            if (nums1[p1] > nums2[p2]) {
                nums1[p] = nums1[p1];
                p1--;
            } else {
                nums1[p] = nums2[p2];
                p2--;
            }
            p--;
        }

        // Step 5: Copy any remaining elements from nums2
        // If p1 >= 0, we don't need to do anything because those elements 
        // are already at the beginning of nums1!
        while (p2 >= 0) {
            nums1[p] = nums2[p2];
            p2--;
            p--;
        }
    }
};

// Helper function to print results
void printResult(std::vector<int> nums1, int m, std::vector<int> nums2, int n, std::vector<int> expected) {
    std::cout << "nums1: [";
    for (size_t i = 0; i < nums1.size(); ++i) std::cout << nums1[i] << (i < nums1.size() - 1 ? ", " : "");
    std::cout << "], m = " << m << "\n";
    
    std::cout << "nums2: [";
    for (size_t i = 0; i < nums2.size(); ++i) std::cout << nums2[i] << (i < nums2.size() - 1 ? ", " : "");
    std::cout << "], n = " << n << "\n";

    Solution solver;
    solver.merge(nums1, m, nums2, n);

    std::cout << "Expected: [";
    for (size_t i = 0; i < expected.size(); ++i) std::cout << expected[i] << (i < expected.size() - 1 ? ", " : "");
    std::cout << "]\nResult:   [";
    for (size_t i = 0; i < nums1.size(); ++i) std::cout << nums1[i] << (i < nums1.size() - 1 ? ", " : "");
    std::cout << "]\n\n";
}

int main() {
    // Test Case 1: Standard case
    std::vector<int> nums1_1 = {1, 2, 3, 0, 0, 0};
    std::vector<int> nums2_1 = {2, 5, 6};
    printResult(nums1_1, 3, nums2_1, 3, {1, 2, 2, 3, 5, 6});

    // Test Case 2: nums2 is empty
    std::vector<int> nums1_2 = {1};
    std::vector<int> nums2_2 = {};
    printResult(nums1_2, 1, nums2_2, 0, {1});

    // Test Case 3: nums1 is empty (only contains the placeholder 0)
    std::vector<int> nums1_3 = {0};
    std::vector<int> nums2_3 = {1};
    printResult(nums1_3, 0, nums2_3, 1, {1});

    // Test Case 4: nums2 has smaller elements than nums1
    std::vector<int> nums1_4 = {4, 5, 6, 0, 0, 0};
    std::vector<int> nums2_4 = {1, 2, 3};
    printResult(nums1_4, 3, nums2_4, 3, {1, 2, 3, 4, 5, 6});

    return 0;
}
