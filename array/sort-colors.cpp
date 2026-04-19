/*
 * ============================================================================
 * LEETCODE 75: SORT COLORS (DUTCH NATIONAL FLAG ALGORITHM)
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - In-place Partitioning: Moving elements around within an array by swapping, 
 * to group them by specific properties without using extra memory.
 * - Three Pointers: Using a scanner pointer (`mid`) to evaluate data, and 
 * boundary pointers (`low` and `high`) to act as landing zones for swapped data.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Initialize `low = 0` (boundary for 0s), `mid = 0` (the scanner), 
 * and `high = n - 1` (boundary for 2s).
 * Step 2: Loop while `mid <= high`. The `<=` is important because `high` 
 * points to an unexplored element that `mid` still needs to evaluate.
 * Step 3: Evaluate `nums[mid]`.
 * Step 4: If it's `0`, swap `nums[low]` and `nums[mid]`. Since `low` only ever 
 * points to `1`s (or `0`s if `low == mid`), the swapped element going into `mid` 
 * is safe. Increment both `low` and `mid`.
 * Step 5: If it's `1`, it's in the correct middle region. Just increment `mid`.
 * Step 6: If it's `2`, swap `nums[mid]` and `nums[high]`. Decrement `high`. 
 * Do NOT increment `mid` because the element swapped from `high` into `mid` 
 * has not been checked yet!
 * Step 7: The array is sorted in-place when `mid` crosses `high`.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - "Trusted" vs "Untrusted" Swaps: When we swap `mid` and `low`, we trust the 
 * element coming into `mid` because `mid` has already scanned past `low`. But 
 * when we swap `mid` and `high`, we are pulling a brand new, unseen element 
 * from the back of the array. That's why we freeze `mid` and check it again.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm> // Required for std::swap

class Solution {
public:
    /**
     * @brief Sorts an array of 0s, 1s, and 2s in-place.
     * Complexity Analysis:
     * - Time: O(n). We process each element at most twice (an element might be 
     * swapped from high to mid, and then from mid to low). The pointers cross 
     * in linear time.
     * - Space: O(1). Modifying the input array in-place.
     */
    void sortColors(std::vector<int>& nums) {
        int low = 0;
        int mid = 0;
        int high = nums.size() - 1;

        // mid is the scout. It stops once it crosses the high boundary.
        while (mid <= high) {
            if (nums[mid] == 0) {
                // Throw the 0 to the left boundary
                std::swap(nums[low], nums[mid]);
                low++;
                mid++;
            } 
            else if (nums[mid] == 1) {
                // 1 is exactly where it belongs
                mid++;
            } 
            else if (nums[mid] == 2) {
                // Throw the 2 to the right boundary
                std::swap(nums[mid], nums[high]);
                high--;
                // DO NOT mid++; We must re-evaluate the new nums[mid].
            }
        }
    }
};

// Helper function to print results
void printResult(std::vector<int> nums, const std::vector<int>& expected) {
    std::cout << "Input:  [";
    for (size_t i = 0; i < nums.size(); ++i) std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "");
    std::cout << "]\n";

    Solution solver;
    solver.sortColors(nums);

    std::cout << "Result: [";
    for (size_t i = 0; i < nums.size(); ++i) std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "");
    std::cout << "]\n";

    std::cout << "Expect: [";
    for (size_t i = 0; i < expected.size(); ++i) std::cout << expected[i] << (i < expected.size() - 1 ? ", " : "");
    std::cout << "]\n\n";
}

int main() {
    // Test Case 1: Standard mix
    std::vector<int> nums1 = {2, 0, 2, 1, 1, 0};
    printResult(nums1, {0, 0, 1, 1, 2, 2});

    // Test Case 2: Already partially sorted
    std::vector<int> nums2 = {2, 0, 1};
    printResult(nums2, {0, 1, 2});

    // Test Case 3: Only one element
    std::vector<int> nums3 = {0};
    printResult(nums3, {0});

    // Test Case 4: Only 1s
    std::vector<int> nums4 = {1, 1, 1};
    printResult(nums4, {1, 1, 1});

    return 0;
}
