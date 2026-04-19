/*
 * ============================================================================
 * LEETCODE 5: MANACHER'S ALGORITHM (ELI5 "BUTTERFLY" VERSION)
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Symmetrical Mirrors: Knowing that if you know what the left side of a 
 * mirror looks like, you automatically know what the right side looks like 
 * without even looking at it.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Put a '#' between every letter so every word has a perfect middle. 
 * Add a '^' at the start and '$' at the end so we don't fall off the edges.
 * Step 2: Keep track of the 'Center' (C) and the 'Right Edge' (R) of the 
 * biggest butterfly we are currently standing inside.
 * Step 3: Walk down the line (loop `i`).
 * Step 4: If `i` is inside `R` (the right wing), find its mirror twin on the 
 * left wing. Copy the left twin's homework (radius).
 * Step 5: Try to grow the butterfly a little bit more just in case it's 
 * bigger than the twin.
 * Step 6: If this new butterfly reaches further right than `R`, make it the 
 * new giant butterfly (Update C and R).
 * Step 7: Find the biggest radius in our notebook and translate it back to 
 * the original word without the '#' sticks.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Never Do Work Twice: If you already calculated the left side of a 
 * palindrome, use math to instantly copy that answer to the right side.
 * - The Power of '#' Formatting: Changing the data format (inserting '#') 
 * makes the algorithm much simpler because it destroys the "even vs odd" 
 * edge cases.
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        // Step 1: Put sticks between the blocks
        std::string T = "^#";
        for (char c : s) {
            T += c;
            T += '#';
        }
        T += "$";
        
        int n = T.size();
        std::vector<int> P(n, 0); // Notebook to store butterfly sizes
        
        int C = 0; // Giant butterfly center
        int R = 0; // Giant butterfly right edge
        
        for (int i = 1; i < n - 1; ++i) {
            
            // Step 4: The Mirror Trick!
            // If we are inside the right wing (i < R), look at the left wing.
            if (R > i) {
                int left_mirror = 2 * C - i; // Math to find the left twin
                P[i] = std::min(R - i, P[left_mirror]); // Copy the twin's size
            } else {
                P[i] = 0; // Outside the wing, start from zero
            }
            
            // Step 5: Try to grow the wings outwards
            while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                P[i]++;
            }
            
            // Step 6: Did we reach further right? Update the giant butterfly!
            if (i + P[i] > R) {
                C = i;
                R = i + P[i];
            }
        }
        
        // Step 7: Find the winner and clean up the sticks
        int max_len = *std::max_element(P.begin(), P.end());
        int center_index = std::distance(P.begin(), std::find(P.begin(), P.end(), max_len));
        
        return s.substr((center_index - max_len) / 2, max_len);
    }
};

// Helper function to print results
void printResult(std::string s, std::string expected, std::string result) {
    std::cout << "Input: \"" << s << "\"\n";
    std::cout << "Expected: \"" << expected << "\" | Result: \"" << result << "\"\n\n";
}

int main() {
    Solution solver;

    // Test Case: The butterfly "aba" is hidden inside
    std::string s1 = "babad";
    printResult(s1, "bab", solver.longestPalindrome(s1));

    return 0;
}
