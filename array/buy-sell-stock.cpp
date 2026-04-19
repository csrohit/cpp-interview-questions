/*
 * ============================================================================
 * LEETCODE 121: BEST TIME TO BUY AND SELL STOCK
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Array Traversal: Iterating through an array in a single pass.
 * - State Tracking: Maintaining running minimums and maximums over time.
 * - Greedy Approach: Making the locally optimal choice at each step (updating 
 * the lowest buy price immediately) to find a global optimum.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Initialize `minPrice` to the maximum possible integer (`INT_MAX`). 
 * This ensures the very first price we see will become the new `minPrice`.
 * Step 2: Initialize `maxProfit` to 0, because we can't have negative profit 
 * (if we can't make a profit, we just don't buy).
 * Step 3: Iterate through each `price` in the array.
 * Step 4: If the `price` is less than `minPrice`, update `minPrice`. 
 * Step 5: Else, calculate the potential profit (`price - minPrice`). If this 
 * profit is strictly greater than `maxProfit`, update `maxProfit`.
 * Step 6: Return the `maxProfit` at the end of the loop.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Track the Past to Evaluate the Present: You don't need nested loops to 
 * check every combination. By maintaining a "running minimum," you carry all 
 * the necessary history with you in a single variable, achieving O(n) time.
 * - Initialization Matters: Always initialize your "minimum tracker" to the 
 * highest possible value, and your "maximum tracker" to the lowest possible 
 * valid value.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // Required for INT_MAX

class Solution {
public:
    /**
     * @brief Calculates the maximum profit achievable from a single buy and sell.
     * Complexity Analysis:
     * - Time: O(n). We traverse the prices array exactly once.
     * - Space: O(1). Only two variables are used, requiring constant extra space.
     */
    int maxProfit(std::vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;

        for (int i = 0; i < prices.size(); ++i) {
            if (prices[i] < minPrice) {
                // Found a cheaper price to buy at
                minPrice = prices[i];
            } else if (prices[i] - minPrice > maxProfit) {
                // Selling today yields a higher profit than we've seen so far
                maxProfit = prices[i] - minPrice;
            }
        }

        return maxProfit;
    }
};

// Helper function to print results
void printResult(std::vector<int> prices, int expected, int result) {
    std::cout << "Prices: [";
    for (size_t i = 0; i < prices.size(); ++i) {
        std::cout << prices[i] << (i < prices.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";
    std::cout << "Expected: " << expected << " | Result: " << result << "\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard case with a clear profit
    std::vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    // Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6 - 1 = 5.
    printResult(prices1, 5, solver.maxProfit(prices1));

    // Test Case 2: Prices continuously dropping (no profit possible)
    std::vector<int> prices2 = {7, 6, 4, 3, 1};
    // In this case, no transaction is done, i.e. max profit = 0.
    printResult(prices2, 0, solver.maxProfit(prices2));

    // Test Case 3: Profit on the very last day
    std::vector<int> prices3 = {2, 4, 1, 10};
    // Buy on day 3 (price = 1), sell on day 4 (price = 10).
    printResult(prices3, 9, solver.maxProfit(prices3));

    return 0;
}
