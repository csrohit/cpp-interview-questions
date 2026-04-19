#include <iostream>
#include <vector>

/**
 * @brief Solution for LeetCode 167: Two Sum II - Input Array Is Sorted.
 * * Pattern: Two Pointers (Opposite Ends).
 * Since the array is already sorted, we can find the target in O(n) time 
 * and O(1) space, avoiding the need for an O(n) Hash Map.
 */
class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;

        while (left < right) {
            int currentSum = numbers[left] + numbers[right];

            if (currentSum == target) {
                // NUANCE: The problem explicitly states the array is "1-indexed".
                // This means the first element is considered index 1, not 0.
                // We must add 1 to both of our pointers before returning them.
                return {left + 1, right + 1};
            } 
            else if (currentSum < target) {
                // Sum is too small, we need a larger number
                left++;
            } 
            else {
                // Sum is too large, we need a smaller number
                right--;
            }
        }

        // The problem guarantees exactly one solution, but C++ expects a return.
        return {}; 
    }
};

// Helper function to print results
void printResult(const std::vector<int>& result) {
    std::cout << "[" << result[0] << ", " << result[1] << "]\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard case
    std::vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    std::cout << "Input: [2, 7, 11, 15], Target: 9\nResult: ";
    printResult(solver.twoSum(nums1, target1));
    std::cout << "Expected: [1, 2]\n\n";

    // Test Case 2: Negative numbers
    std::vector<int> nums2 = {-1, 0};
    int target2 = -1;
    std::cout << "Input: [-1, 0], Target: -1\nResult: ";
    printResult(solver.twoSum(nums2, target2));
    std::cout << "Expected: [1, 2]\n\n";

    // Test Case 3: Duplicates that form the target
    std::vector<int> nums3 = {2, 3, 4, 4, 9, 56};
    int target3 = 8;
    std::cout << "Input: [2, 3, 4, 4, 9, 56], Target: 8\nResult: ";
    printResult(solver.twoSum(nums3, target3));
    std::cout << "Expected: [3, 4]\n";

    return 0;
}
