#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

/**
 * @brief Solution for LeetCode 128: Longest Consecutive Sequence.
 * * Pattern: Hash Set Boundary Identification.
 * By only building sequences from the "start" of a sequence, we ensure 
 * each number is visited at most twice, guaranteeing O(n) time complexity.
 */
class Solution {
public:
    int longestConsecutive(std::vector<int>& nums) {
        // Step 1: Dump all numbers into a Hash Set for O(1) lookups.
        std::unordered_set<int> numSet(nums.begin(), nums.end());
        int longestStreak = 0;

        // Step 2: Iterate through the SET (or array, both work)
        for (int num : numSet) {
            
            // Step 3: Check if this number is the START of a sequence.
            // If num - 1 exists, this is NOT the start, so we skip it.
            if (numSet.find(num - 1) == numSet.end()) {
                
                // We found a start! Begin counting upwards.
                int currentNum = num;
                int currentStreak = 1;

                while (numSet.find(currentNum + 1) != numSet.end()) {
                    currentNum += 1;
                    currentStreak += 1;
                }

                // Step 4: Update our maximum streak
                longestStreak = std::max(longestStreak, currentStreak);
            }
        }

        return longestStreak;
    }
};

int main() {
    Solution solver;

    // Test Case 1: Standard case
    std::vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    std::cout << "Input: [100, 4, 200, 1, 3, 2]\n";
    std::cout << "Expected: 4 | Result: " << solver.longestConsecutive(nums1) << "\n\n";

    // Test Case 2: Sequence with duplicates
    std::vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    std::cout << "Input: [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]\n";
    std::cout << "Expected: 9 | Result: " << solver.longestConsecutive(nums2) << "\n\n";

    // Test Case 3: Empty array
    std::vector<int> nums3 = {};
    std::cout << "Input: []\n";
    std::cout << "Expected: 0 | Result: " << solver.longestConsecutive(nums3) << "\n\n";

    return 0;
}
