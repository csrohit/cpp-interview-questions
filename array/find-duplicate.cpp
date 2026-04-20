/*
 * ============================================================================
 * LEETCODE 287: FIND THE DUPLICATE NUMBER
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Array as a Graph/Linked List: Treating `nums[i]` not as a value, but as 
 * a "next" pointer leading to index `nums[i]`.
 * - Floyd's Cycle Detection Algorithm: Using a slow and fast pointer to find 
 * a loop, and then using a mathematical distance trick to find where the loop 
 * begins.
 * - Pigeonhole Principle: If you have N boxes and N+1 items, at least one 
 * box must contain multiple items. This guarantees a duplicate exists.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Initialize both the `tortoise` and `hare` at the start of the 
 * "Linked List", which is `nums[0]`.
 * Step 2: Start a `do-while` loop. The `tortoise` moves to `nums[tortoise]`. 
 * The `hare` moves to `nums[nums[hare]]`.
 * Step 3: When `tortoise == hare`, they have intersected inside the cycle. 
 * Break the loop.
 * Step 4: To find the cycle's entrance, place a new pointer (`cycleFinder`) 
 * back at the starting line `nums[0]`.
 * Step 5: Start a `while` loop. Move both `cycleFinder` and `tortoise` one 
 * step at a time (`nums[pointer]`).
 * Step 6: When they collide, you have found the entrance to the cycle. 
 * Return this value.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Time/Space Mastery: This is one of the only ways to solve this problem 
 * in strict O(n) time and O(1) space without modifying the original array 
 * (which rules out array negation or sorting).
 * ============================================================================
 */

#include <iostream>
#include <vector>

class Solution {
public:
    /**
     * @brief Finds the single duplicate number in the array.
     * Complexity Analysis:
     * - Time: O(n). Phase 1 guarantees an intersection in linear time. Phase 2 
     * guarantees finding the cycle entrance in linear time.
     * - Space: O(1). We only use three integer variables to track indices.
     */
    int findDuplicate(const std::vector<int>& nums) {
        // Phase 1: Find the intersection point inside the loop
        int tortoise = nums[0];
        int hare = nums[0];

        do {
            tortoise = nums[tortoise];       // Move 1 step
            hare = nums[nums[hare]];         // Move 2 steps
        } while (tortoise != hare);

        // Phase 2: Find the entrance to the cycle
        int cycleFinder = nums[0];
        
        while (cycleFinder != tortoise) {
            cycleFinder = nums[cycleFinder]; // Move 1 step
            tortoise = nums[tortoise];       // Move 1 step
        }

        // They crash exactly at the cycle entrance, which is our duplicate
        return cycleFinder;
    }
};

// Helper function to print results
void printResult(const std::vector<int>& nums, int expected, int result) {
    std::cout << "Input: [";
    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";
    std::cout << "Expected Duplicate: " << expected << " | Result: " << result << "\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard case
    // 1 points to 3. 3 points to 2. 2 points to 4. 4 points to 2 (Cycle!).
    std::vector<int> nums1 = {1, 3, 4, 2, 2};
    printResult(nums1, 2, solver.findDuplicate(nums1));

    // Test Case 2: Duplicate at the very beginning
    std::vector<int> nums2 = {3, 1, 3, 4, 2};
    printResult(nums2, 3, solver.findDuplicate(nums2));

    // Test Case 3: Multiple instances of the same duplicate
    std::vector<int> nums3 = {3, 3, 3, 3, 3};
    printResult(nums3, 3, solver.findDuplicate(nums3));

    return 0;
}
