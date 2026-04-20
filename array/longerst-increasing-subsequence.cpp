/*
 * ============================================================================
 * LEETCODE 300: LONGEST INCREASING SUBSEQUENCE
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Greedy Approach with Binary Search: Maintaining an ongoing optimal state 
 * and using binary search (O(log n)) to update that state quickly.
 * - std::lower_bound: The C++ standard library function for binary searching 
 * an ordered array to find the first element that is >= a target value.
 *
 * 2. THE "BEST TAILS" CONCEPT (CRITICAL):
 * ---------------------------------------
 * The array we are building (`bestTails`) does NOT hold the actual longest 
 * increasing subsequence. If you try to read it as a sequence, it will look 
 * like a Frankenstein monster.
 * * Instead, it is a mathematical log. You must read it like this:
 * Every index `i` in the `bestTails` array represents the best (smallest) 
 * ending number for a valid subsequence of length `i + 1`.
 * * Example trace of [2, 5, 8, 4]:
 * - Insert 2: [2]       -> Best sequence of length 1 ends in 2.
 * - Insert 5: [2, 5]    -> Best sequence of length 2 ends in 5.
 * - Insert 8: [2, 5, 8] -> Best sequence of length 3 ends in 8. (Max length = 3)
 * - Insert 4: [2, 4, 8] -> The 5 is overwritten! 
 * The best sequence of length 2 NOW ends in 4.
 * The 8 remains to prove length 3 was achieved in the past.
 *
 * 3. STEPS TO SOLVE:
 * ------------------
 * Step 1: Create an empty vector `bestTails`.
 * Step 2: Iterate through every `currentNumber` in the input array.
 * Step 3: If `bestTails` is empty, OR if `currentNumber` safely extends our 
 * max length (it is strictly greater than the last tail), push it to the back.
 * Step 4: If it is not greater, we perform a "Smart Replacement". We use 
 * `std::lower_bound` to find the iterator (laser pointer) pointing to the 
 * first bulky tail that is >= `currentNumber`.
 * Step 5: Dereference that iterator (`*`) and overwrite the bulky tail with 
 * our sleeker `currentNumber`.
 * Step 6: Return the size of `bestTails`, which strictly equals the max length.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    /**
     * @brief Finds the length of the longest strictly increasing subsequence.
     * Complexity Analysis:
     * - Time: O(n log n). We iterate through the array of 'n' elements once. 
     * Inside the loop, `std::lower_bound` performs a binary search taking O(log n).
     * - Space: O(n). In the worst case (a strictly increasing array), the 
     * `bestTails` array will grow to the size of the input array.
     */
    int lengthOfLIS(const std::vector<int>& nums) {
        // This array logs the smallest possible tail for a sequence of a given length
        std::vector<int> bestTails;

        for (int currentNumber : nums) {
            
            // Scenario 1: The current number safely extends our record length
            if (bestTails.empty() || currentNumber > bestTails.back()) {
                bestTails.push_back(currentNumber);
            } 
            // Scenario 2: Smart Replacement (Update historical checkpoints)
            else {
                // Find the laser pointer (iterator) to the first bulky tail >= currentNumber
                auto iteratorToReplace = std::lower_bound(bestTails.begin(), bestTails.end(), currentNumber);
                
                // Dereference the pointer to overwrite the old bulky tail with the sleeker one
                *iteratorToReplace = currentNumber;
            }
        }

        // The overall size of our mathematical log represents the max length found
        return bestTails.size();
    }
};

// Helper function to print results
void printResult(const std::vector<int>& nums, int expected, int result) {
    std::cout << "Input: [";
    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";
    std::cout << "Expected LIS Length: " << expected << " | Result: " << result << "\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard case
    std::vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    // LIS is [2, 3, 7, 101] or [2, 3, 7, 18]. Length is 4.
    printResult(nums1, 4, solver.lengthOfLIS(nums1));

    // Test Case 2: All same elements
    std::vector<int> nums2 = {7, 7, 7, 7, 7, 7, 7};
    // Must be strictly increasing, so length is 1.
    printResult(nums2, 1, solver.lengthOfLIS(nums2));

    // Test Case 3: The "Frankenstein Array" Proof
    std::vector<int> nums3 = {4, 5, 6, 3};
    // bestTails ends physically looking like [3, 5, 6], but the true LIS is [4, 5, 6]. 
    // The length is safely and correctly 3.
    printResult(nums3, 3, solver.lengthOfLIS(nums3));

    // Test Case 4: The value of Smart Replacement
    std::vector<int> nums4 = {2, 5, 8, 4, 5, 6};
    // Replacing 5 with 4 allows the subsequent 5 and 6 to attach and build [2, 4, 5, 6].
    printResult(nums4, 4, solver.lengthOfLIS(nums4));

    return 0;
}