/*
 * ============================================================================
 * LEETCODE 412: FIZZ BUZZ
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Modulo Arithmetic (`%`): The modulo operator returns the remainder of a 
 * division. If `a % b == 0`, then `a` is perfectly divisible by `b`.
 * - Control Flow (If-Else If): Understanding that an `if-else if` chain 
 * executes the FIRST true condition and skips the rest.
 * - String Conversion: Knowing how to convert an integer to a string in C++ 
 * using `std::to_string()`.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Initialize an empty string vector `result` of size `n` (or push_back).
 * Step 2: Loop `i` from 1 up to and including `n`.
 * Step 3: The Most Restrictive Check FIRST: Check if `i % 15 == 0` (which 
 * means it is divisible by both 3 and 5). If true, append "FizzBuzz".
 * Step 4: Check if `i % 3 == 0`. If true, append "Fizz".
 * Step 5: Check if `i % 5 == 0`. If true, append "Buzz".
 * Step 6: The Fallback Check: If none of the above are true, append the 
 * number `i` converted to a string.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Order of Operations Matters: In an `if-else if` block, always put the 
 * most specific/restrictive condition at the very top. If you check `i % 3` 
 * first, the number 15 will output "Fizz" and the chain will terminate prematurely.
 * - String Concatenation Pattern (Bonus): For a highly extensible FizzBuzz 
 * (e.g., adding rules like "divisible by 7 is Bazz"), you can build an empty 
 * string `s`, append "Fizz" if % 3, append "Buzz" if % 5, and if `s` is still 
 * empty at the end, set it to the number. This avoids checking combinations!
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>

/**
 * @brief Solution for LeetCode 412: Fizz Buzz.
 * * Pattern: Modulo Arithmetic & Control Flow.
 */
class Solution {
public:
    /**
     * @brief Generates the FizzBuzz string array up to n.
     * Complexity Analysis:
     * - Time: O(n). We iterate from 1 to n exactly once.
     * - Space: O(1) auxiliary space (excluding the output array).
     */
    std::vector<std::string> fizzBuzz(int n) {
        std::vector<std::string> result;
        // Optimization: Reserve space to prevent reallocation
        result.reserve(n); 

        for (int i = 1; i <= n; ++i) {
            // Check the most restrictive condition first (divisible by 15)
            if (i % 15 == 0) {
                result.push_back("FizzBuzz");
            } 
            else if (i % 3 == 0) {
                result.push_back("Fizz");
            } 
            else if (i % 5 == 0) {
                result.push_back("Buzz");
            } 
            else {
                result.push_back(std::to_string(i));
            }
        }

        return result;
    }
};

// Helper function to print results
void printResult(int n, const std::vector<std::string>& result) {
    std::cout << "Input: n = " << n << "\nResult: [";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "\"" << result[i] << "\"" << (i < result.size() - 1 ? ", " : "");
    }
    std::cout << "]\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Base case
    int n1 = 3;
    printResult(n1, solver.fizzBuzz(n1));

    // Test Case 2: Up to 5
    int n2 = 5;
    printResult(n2, solver.fizzBuzz(n2));

    // Test Case 3: Reaching the FizzBuzz condition
    int n3 = 15;
    printResult(n3, solver.fizzBuzz(n3));

    return 0;
}
