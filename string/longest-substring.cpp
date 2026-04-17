#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/**
 * @brief Solution for LeetCode 3: Longest Substring Without Repeating Characters.
 * * Strategy: Optimized Sliding Window.
 * * We maintain a "window" of unique characters using two pointers: 'left' and 'right'.
 * As 'right' moves, we expand the window. If we hit a duplicate, we "jump" the 
 * 'left' pointer to just after the previous occurrence of that character.
 */
class Solution {
public:
    /**
     * @param s The input string.
     * @return The length of the longest substring without repeating characters.
     * * Complexity Analysis:
     * - Time: O(n), where n is the length of the string. We visit each char once.
     * - Space: O(k), where k is the size of the character set (128 for ASCII). 
     * Since 128 is constant, this is often called O(1) space.
     */
    int lengthOfLongestSubstring(std::string s) {
        // 128 is the size of the standard ASCII character set.
        // Using a vector is faster than std::unordered_map due to cache locality.
        // We initialize with -1 to indicate the character hasn't been seen yet.
        std::vector<int> lastSeen(128, -1);
        
        int maxLength = 0;
        int left = 0; // Start of the current window

        for (int right = 0; right < s.length(); ++right) {
            char currentChar = s[right];

            // NUANCE: Check if we've seen this character AND if its last 
            // recorded position is actually within our current window.
            if (lastSeen[currentChar] >= left) {
                // JUMP: Instead of incrementing 'left' one by one, we move it 
                // directly past the first instance of the duplicate.
                left = lastSeen[currentChar] + 1;
            }

            // Update/Record the index where this character was last spotted
            lastSeen[currentChar] = right;

            // Calculate the current window size (right - left + 1) and update max
            maxLength = std::max(maxLength, right - left + 1);
        }

        return maxLength;
    }
};

int main() {
    Solution solver;

    // Test Case 1: Standard case
    std::string s1 = "abcabcbb";
    std::cout << "Input: " << s1 << "\nExpected: 3 | Result: " 
              << solver.lengthOfLongestSubstring(s1) << "\n\n";

    // Test Case 2: All identical
    std::string s2 = "bbbbb";
    std::cout << "Input: " << s2 << "\nExpected: 1 | Result: " 
              << solver.lengthOfLongestSubstring(s2) << "\n\n";

    // Test Case 3: Mixed unique and repeats
    std::string s3 = "pwwkew";
    std::cout << "Input: " << s3 << "\nExpected: 3 | Result: " 
              << solver.lengthOfLongestSubstring(s3) << "\n\n";

    // Test Case 4: Empty string
    std::string s4 = "";
    std::cout << "Input: \"\"" << "\nExpected: 0 | Result: " 
              << solver.lengthOfLongestSubstring(s4) << "\n\n";

    return 0;
}
