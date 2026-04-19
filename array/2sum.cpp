/*
 * ============================================================================
 * LEETCODE 1: TWO SUM
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Hash Maps (std::unordered_map in C++): You must understand how Hash Maps 
 * provide O(1) average time complexity for lookups and insertions.
 * - Space-Time Tradeoff: Understanding that we can drastically reduce our 
 * execution time by using extra memory (the Hash Map).
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Create an empty `std::unordered_map` to store numbers we have 
 * visited and their respective indices.
 * Step 2: Iterate through the array `nums` using a standard `for` loop.
 * Step 3: For each element, calculate its `complement` (target - nums[i]).
 * Step 4: Check if the `complement` exists in the Hash Map.
 * Step 5: If it exists, we have found our two numbers! Return the index 
 * stored in the map and our current index `i`.
 * Step 6: If it does not exist, insert the current number and its index 
 * into the map so future numbers can look it up.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - The "Complement" Pattern: Whenever a problem asks you to find two items 
 * that combine to form a specific state or target, calculate the exact 
 * "missing piece" (complement) and use a Hash Set/Map to look for it.
 * - Single-Pass Efficiency: Notice that we don't need to populate the Hash 
 * Map completely before searching it. By searching *before* we insert, we 
 * ensure a number doesn't accidentally pair with itself, and we solve the 
 * problem in exactly one pass!
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <unordered_map>

/**
 * @brief Solution for LeetCode 1: Two Sum.
 * * Pattern: Hash Map.
 * By using a Hash Map to store previously seen numbers, we can instantly 
 * check if the required "complement" exists, reducing time complexity from 
 * O(n^2) to O(n).
 */
class Solution {
public:
    /**
     * @brief Finds the indices of the two numbers that add up to the target.
     * Complexity Analysis:
     * - Time: O(n). We traverse the list containing n elements exactly once. 
     * Each lookup in the hash map costs O(1) average time.
     * - Space: O(n). The extra space required depends on the number of items 
     * stored in the hash map, which stores at most n elements.
     */
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        // Map stores -> {number_value : index_in_array}
        std::unordered_map<int, int> numMap;

        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];

            // If the complement is found in our map
            if (numMap.count(complement)) {
                // Return the index of the complement and our current index
                return {numMap[complement], i};
            }

            // Otherwise, add the current number and its index to the map
            numMap[nums[i]] = i;
        }

        // Return empty vector if no solution is found (though the problem 
        // guarantees one valid answer exists)
        return {};
    }
};

// Helper function to print results
void printResult(std::vector<int> nums, int target, std::vector<int> expected, std::vector<int> result) {
    std::cout << "Input: [";
    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "");
    }
    std::cout << "], Target: " << target << "\n";
    std::cout << "Expected: [" << expected[0] << ", " << expected[1] << "] | ";
    std::cout << "Result: [" << result[0] << ", " << result[1] << "]\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard case
    std::vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    printResult(nums1, target1, {0, 1}, solver.twoSum(nums1, target1));

    // Test Case 2: Negative numbers and out of order
    std::vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    printResult(nums2, target2, {1, 2}, solver.twoSum(nums2, target2));

    // Test Case 3: Duplicate numbers that form the target
    std::vector<int> nums3 = {3, 3};
    int target3 = 6;
    printResult(nums3, target3, {0, 1}, solver.twoSum(nums3, target3));

    return 0;
}
