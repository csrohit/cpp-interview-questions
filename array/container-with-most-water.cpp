/*
 * ============================================================================
 * LEETCODE 11: CONTAINER WITH MOST WATER
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Two Pointers (Converging): Placing pointers at the opposite ends of an 
 * array and moving them toward the center based on a logical condition.
 * - Greedy Algorithm Strategy: Making the locally optimal choice at each step 
 * (throwing away the shorter line) in the hope of finding a global optimum.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Initialize two pointers: `left = 0` and `right = n - 1`.
 * Step 2: Initialize `max_area = 0` to keep track of the largest container.
 * Step 3: Loop while `left < right`. (Once they meet, the width is 0).
 * Step 4: Calculate the `current_width` as `right - left`.
 * Step 5: Calculate the `current_height` as the minimum of the two heights 
 * pointed to by `left` and `right`.
 * Step 6: Calculate `current_area = current_width * current_height`. Update 
 * `max_area` if this is the largest we've seen.
 * Step 7: The Greedy Choice: Compare `height[left]` and `height[right]`. 
 * Increment `left` if the left line is shorter; otherwise, decrement `right`.
 * Step 8: Return `max_area` when the pointers cross.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Logical Elimination: The brilliance of this algorithm is that by moving 
 * the shorter line, you are effectively eliminating all possible combinations 
 * involving that shorter line. You know none of them could possibly be better 
 * because the width would shrink and the height couldn't get any taller than 
 * that short line. This is how we skip O(n^2) checks!
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm> // Required for std::min and std::max

class Solution {
public:
    /**
     * @brief Finds the maximum area of water a container can store.
     * Complexity Analysis:
     * - Time: O(n). We traverse the array exactly once as the two pointers 
     * converge toward the middle.
     * - Space: O(1). We only use a few integer variables for tracking state.
     */
    int maxArea(std::vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int max_area = 0;

        while (left < right) {
            // Calculate the dimensions of the current container
            int current_width = right - left;
            int current_height = std::min(height[left], height[right]);
            
            // Calculate the area and update the global record
            int current_area = current_width * current_height;
            max_area = std::max(max_area, current_area);

            // Move the pointer pointing to the shorter line
            // If they are equal, moving either one is fine.
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return max_area;
    }
};

// Helper function to print results
void printResult(std::vector<int> height, int expected, int result) {
    std::cout << "Input Heights: [";
    for (size_t i = 0; i < height.size(); ++i) {
        std::cout << height[i] << (i < height.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";
    std::cout << "Expected Area: " << expected << " | Result Area: " << result << "\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard LeetCode example
    std::vector<int> height1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    // The max area is formed between the lines at index 1 (height 8) 
    // and index 8 (height 7). Width = 7, Height = min(8, 7) = 7. Area = 49.
    printResult(height1, 49, solver.maxArea(height1));

    // Test Case 2: Only two lines
    std::vector<int> height2 = {1, 1};
    // Width = 1, Height = min(1, 1) = 1. Area = 1.
    printResult(height2, 1, solver.maxArea(height2));

    // Test Case 3: Decreasing heights
    std::vector<int> height3 = {4, 3, 2, 1, 4};
    // Formed by the two 4s at the ends. Width = 4, Height = 4. Area = 16.
    printResult(height3, 16, solver.maxArea(height3));

    return 0;
}
