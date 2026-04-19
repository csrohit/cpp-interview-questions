/*
 * ============================================================================
 * LEETCODE 1200: MINIMUM ABSOLUTE DIFFERENCE
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Sorting: Understanding that sorting an array reduces proximity problems 
 * (like finding closest values) from O(n^2) to O(n log n).
 * - Array Traversal: Iterating through an array while comparing adjacent elements 
 * (using i and i-1).
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Sort the array `arr` in ascending order.
 * Step 2: Initialize `minDiff` to the maximum possible integer to guarantee 
 * the first pair sets the initial record.
 * Step 3: Create a 2D vector `result` to store the valid pairs.
 * Step 4: Iterate through the array starting from index 1.
 * Step 5: Calculate `currentDiff = arr[i] - arr[i-1]`.
 * Step 6: If `currentDiff < minDiff`, we found a new absolute minimum. Update 
 * `minDiff`, clear the `result` vector of any previous pairs, and push the 
 * current pair.
 * Step 7: If `currentDiff == minDiff`, push the current pair to `result` 
 * without clearing it.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Sorting as a Math Tool: Sorting places elements on a number line. The 
 * closest two numbers will NEVER have another number between them, meaning 
 * you only ever need to check immediate neighbors.
 * - The "Clear and Replace" Optimization: Instead of doing two passes (one 
 * to find the min difference, and a second to collect the pairs), you can 
 * do it in one pass by clearing your results array whenever a strictly smaller 
 * difference is discovered.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    /**
     * @brief Finds all pairs of elements with the minimum absolute difference.
     * Complexity Analysis:
     * - Time: O(n log n) due to the sorting step. The subsequent traversal is O(n).
     * - Space: O(1) auxiliary space (excluding the output vector and sorting stack).
     */
    std::vector<std::vector<int>> minimumAbsDifference(std::vector<int>& arr) {
        std::vector<std::vector<int>> result;
        
        // Step 1: Sort the array
        std::sort(arr.begin(), arr.end());
        
        // Step 2: Initialize minDiff
        int minDiff = INT_MAX;

        // Step 4: Iterate and compare adjacent elements
        for (int i = 1; i < arr.size(); ++i) {
            int currentDiff = arr[i] - arr[i-1];

            // Step 6: New minimum found
            if (currentDiff < minDiff) {
                minDiff = currentDiff;
                result.clear(); // Discard pairs that are no longer the minimum
                result.push_back({arr[i-1], arr[i]});
            } 
            // Step 7: Tie for the minimum
            else if (currentDiff == minDiff) {
                result.push_back({arr[i-1], arr[i]});
            }
        }

        return result;
    }
};

// Helper function to print results
void printResult(std::vector<int> arr, const std::vector<std::vector<int>>& result) {
    std::cout << "Input: [";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << (i < arr.size() - 1 ? ", " : "");
    }
    std::cout << "]\nResult: [";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "[" << result[i][0] << ", " << result[i][1] << "]";
        if (i < result.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard case
    std::vector<int> arr1 = {4, 2, 1, 3};
    // Sorted: [1, 2, 3, 4]. Min diff is 1.
    printResult(arr1, solver.minimumAbsDifference(arr1));

    // Test Case 2: Larger differences
    std::vector<int> arr2 = {1, 3, 6, 10, 15};
    // Sorted already. Min diff is 2 (between 1 and 3).
    printResult(arr2, solver.minimumAbsDifference(arr2));

    // Test Case 3: Negative numbers and multiple pairs
    std::vector<int> arr3 = {3, 8, -10, 23, 19, -4, -14, 27};
    // Sorted: [-14, -10, -4, 3, 8, 19, 23, 27]
    // Min diff is 4: [-14,-10], [19,23], [23,27]
    printResult(arr3, solver.minimumAbsDifference(arr3));

    return 0;
}
