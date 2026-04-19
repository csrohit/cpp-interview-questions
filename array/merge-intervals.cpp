/*
 * ============================================================================
 * LEETCODE 56: MERGE INTERVALS
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Array Sorting: Understanding how to sort a 2D array (matrix). In C++, 
 * `std::sort` on a `vector<vector<int>>` automatically sorts lexicographically, 
 * meaning it perfectly sorts by the first element (start time), and breaks 
 * ties using the second element.
 * - In-place Output Modification: Using the `back()` function in C++ to directly 
 * reference and modify the last element added to our results vector.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Handle the edge case of an empty array.
 * Step 2: Sort the `intervals` array. This is the crux of the algorithm, 
 * reducing an O(n^2) problem into an O(n log n) problem.
 * Step 3: Initialize a `merged` vector and push the first interval into it to 
 * establish our baseline.
 * Step 4: Iterate through the remaining intervals starting from index 1.
 * Step 5: Check for overlap: Is `current_interval[0]` (start) <= 
 * `merged.back()[1]` (the end of the last recorded interval)?
 * Step 6: If they overlap, update the end time of the last recorded interval. 
 * MUST use `std::max()` to ensure we don't accidentally shrink the interval.
 * Step 7: If they do not overlap, simply push the `current_interval` into 
 * the `merged` list.
 * Step 8: Return the `merged` list.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - The "Swallow" Edge Case: Why use `max(old_end, new_end)`? Consider the 
 * intervals [1, 5] and [2, 4]. They overlap. If we just blindly set the new end 
 * to the second interval's end (4), our merged interval becomes [1, 4], which 
 * is WRONG. The first interval completely swallowed the second, so the end 
 * remains 5. `std::max(5, 4)` mathematically protects against this.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    /**
     * @brief Merges all overlapping intervals.
     * Complexity Analysis:
     * - Time: O(n log n). Sorting the intervals dominates the time complexity. 
     * The subsequent linear scan takes O(n) time.
     * - Space: O(log n) or O(n). Depending on the underlying sorting algorithm 
     * (like IntroSort in C++), sorting takes O(log n) auxiliary space. If we 
     * exclude the space needed for the output array, this is O(log n).
     */
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
        if (intervals.empty()) {
            return {};
        }

        // Step 2: Sort intervals by start time
        std::sort(intervals.begin(), intervals.end());

        std::vector<std::vector<int>> merged;
        
        // Step 3: Add the first interval as the baseline
        merged.push_back(intervals[0]);

        // Step 4: Iterate and merge
        for (int i = 1; i < intervals.size(); ++i) {
            
            // Step 5: Check if the current interval starts before or when the last one ends
            if (intervals[i][0] <= merged.back()[1]) {
                
                // Step 6: Overlap found. Update the end time.
                merged.back()[1] = std::max(merged.back()[1], intervals[i][1]);
                
            } else {
                
                // Step 7: Gap found. Push the current interval as a new standalone block.
                merged.push_back(intervals[i]);
            }
        }

        return merged;
    }
};

// Helper function to print results
void printResult(std::vector<std::vector<int>> intervals, const std::vector<std::vector<int>>& expected, const std::vector<std::vector<int>>& result) {
    std::cout << "Input: [";
    for (size_t i = 0; i < intervals.size(); ++i) {
        std::cout << "[" << intervals[i][0] << "," << intervals[i][1] << "]" << (i < intervals.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";
    
    std::cout << "Expected: [";
    for (size_t i = 0; i < expected.size(); ++i) {
        std::cout << "[" << expected[i][0] << "," << expected[i][1] << "]" << (i < expected.size() - 1 ? ", " : "");
    }
    std::cout << "] | Result: [";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "[" << result[i][0] << "," << result[i][1] << "]" << (i < result.size() - 1 ? ", " : "");
    }
    std::cout << "]\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard overlapping intervals
    std::vector<std::vector<int>> intervals1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    printResult(intervals1, {{1, 6}, {8, 10}, {15, 18}}, solver.merge(intervals1));

    // Test Case 2: Touching edges (e.g., meeting ends exactly at 4, next starts at 4)
    std::vector<std::vector<int>> intervals2 = {{1, 4}, {4, 5}};
    printResult(intervals2, {{1, 5}}, solver.merge(intervals2));

    // Test Case 3: Completely swallowed interval (out of order input)
    std::vector<std::vector<int>> intervals3 = {{1, 4}, {0, 4}};
    // Sorted becomes [0, 4], [1, 4]. [1, 4] is completely swallowed.
    printResult(intervals3, {{0, 4}}, solver.merge(intervals3));

    // Test Case 4: Multiple overlaps chaining together into one massive block
    std::vector<std::vector<int>> intervals4 = {{1, 4}, {2, 3}, {3, 6}, {5, 7}};
    printResult(intervals4, {{1, 7}}, solver.merge(intervals4));

    return 0;
}
