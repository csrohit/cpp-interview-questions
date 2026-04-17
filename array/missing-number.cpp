#include <iostream>
#include <vector>

/**
 * @brief Solution for LeetCode 268: Missing Number.
 * Both methods are O(n) Time and O(1) Space.
 */
class Solution {
public:
    /**
     * @brief Method 1: Mathematical Sum
     * Best when n is small enough that n*(n+1) won't cause integer overflow.
     */
    int missingNumberMath(std::vector<int>& nums) {
        // n is the size of the array
        long long n = nums.size(); 
        
        // Expected sum of 0 through n
        long long expectedSum = n * (n + 1) / 2; 
        
        // Actual sum of the elements in the array
        long long actualSum = 0;
        for (int num : nums) {
            actualSum += num;
        }
        
        // The difference is our missing number
        return expectedSum - actualSum;
    }

    /**
     * @brief Method 2: Bitwise XOR
     * Completely immune to integer overflow. The safest choice for large arrays.
     */
    int missingNumberXOR(std::vector<int>& nums) {
        // Initialize missing with 'n' because the loop indices only go up to n-1
        int missing = nums.size(); 
        
        for (int i = 0; i < nums.size(); ++i) {
            // XOR the index (Expected) and the value (Actual)
            missing ^= i ^ nums[i];
        }
        
        return missing;
    }
};

int main() {
    Solution solver;

    // Test Case 1: Missing in the middle
    std::vector<int> nums1 = {3, 0, 1};
    std::cout << "Input: [3, 0, 1]\n";
    std::cout << "Math Result: " << solver.missingNumberMath(nums1) << "\n";
    std::cout << "XOR Result:  " << solver.missingNumberXOR(nums1) << "\n\n";

    // Test Case 2: Missing the 'n' (the largest number)
    std::vector<int> nums2 = {0, 1};
    std::cout << "Input: [0, 1]\n";
    std::cout << "Math Result: " << solver.missingNumberMath(nums2) << "\n";
    std::cout << "XOR Result:  " << solver.missingNumberXOR(nums2) << "\n\n";

    // Test Case 3: Missing 0
    std::vector<int> nums3 = {9, 6, 4, 2, 3, 5, 7, 0, 1};
    std::cout << "Input: [9, 6, 4, 2, 3, 5, 7, 0, 1]\n";
    std::cout << "Math Result: " << solver.missingNumberMath(nums3) << "\n";
    std::cout << "XOR Result:  " << solver.missingNumberXOR(nums3) << "\n";

    return 0;
}
