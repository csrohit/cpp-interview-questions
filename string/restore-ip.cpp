/*
 * ============================================================================
 * LEETCODE 93: RESTORE IP ADDRESSES
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Backtracking / DFS: A technique for solving problems recursively by trying 
 * to build a solution incrementally, one piece at a time, removing those 
 * solutions that fail to satisfy the constraints.
 * - String Manipulation: Extracting substrings and converting them to integers.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Handle length edge cases immediately. A valid IP string MUST be 
 * between 4 and 12 characters long.
 * Step 2: Create a recursive `backtrack` function that tracks the current 
 * index in the string and a vector holding the currently selected segments.
 * Step 3: Base Case -> If the segment vector has exactly 4 items, check if 
 * the `startIndex` has reached the end of the string. If yes, we found a 
 * valid IP! Join the segments with `.` and push to results. Return regardless.
 * Step 4: The Loop -> Iterate `len` from 1 to 3. Extract the substring of 
 * length `len` starting at `startIndex`.
 * Step 5: Validate -> Check if the extracted segment is valid (no leading 
 * zeros for multi-digit numbers, and <= 255).
 * Step 6: Backtrack -> If valid, push the segment to the tracking vector, 
 * recursively call `backtrack` moving the `startIndex` forward by `len`, 
 * and then pop the segment off the vector once the recursion returns.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Constant Time Complexity Bound: Because the depth of the recursion tree 
 * is strictly limited to 4 (the number of IP segments), and the branches are 
 * strictly limited to 3 (lengths 1, 2, or 3), the time complexity is bounded 
 * by a constant O(3^4). It doesn't scale with N, making it incredibly fast.
 * - The "Push, Recurse, Pop" Pattern: This is the exact heartbeat of every 
 * backtracking algorithm. You alter the state, pass it to the next function 
 * call, and then revert the state so the next loop iteration starts clean.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    /**
     * @brief Finds all valid IP addresses that can be formed from the string.
     * Complexity Analysis:
     * - Time: O(1) or bounded to O(3^4). Since an IP address has exactly 4 parts 
     * and each part has at most 3 digits, the number of combinations is fixed 
     * at 3^4 = 81 maximum iterations, regardless of string length.
     * - Space: O(1). The recursion depth is at most 4, and the temporary array 
     * holds at most 4 strings.
     */
    std::vector<std::string> restoreIpAddresses(std::string s) {
        std::vector<std::string> results;
        std::vector<std::string> currentIP;

        // Optimization: Impossible to form an IP address
        if (s.length() < 4 || s.length() > 12) {
            return results;
        }

        backtrack(s, 0, currentIP, results);
        return results;
    }

private:
    void backtrack(const std::string& s, int startIndex, std::vector<std::string>& currentIP, std::vector<std::string>& results) {
        // Step 3: Base Case
        if (currentIP.size() == 4) {
            if (startIndex == s.length()) {
                // We successfully parsed the whole string into 4 segments
                results.push_back(currentIP[0] + "." + currentIP[1] + "." + currentIP[2] + "." + currentIP[3]);
            }
            return; // Return whether it was valid or not
        }

        // Step 4: Explore choices (take 1, 2, or 3 characters)
        for (int len = 1; len <= 3; ++len) {
            // Out of bounds check
            if (startIndex + len > s.length()) {
                break; 
            }

            std::string segment = s.substr(startIndex, len);

            // Step 5: Validate
            if (isValid(segment)) {
                // Step 6: Push, Recurse, Pop
                currentIP.push_back(segment);                  // Choose
                backtrack(s, startIndex + len, currentIP, results); // Explore
                currentIP.pop_back();                          // Un-choose (Backtrack)
            }
        }
    }

    bool isValid(const std::string& segment) {
        // Leading zero check
        if (segment.length() > 1 && segment[0] == '0') {
            return false;
        }
        
        // Bounds check (needs to be <= 255)
        // std::stoi safely converts the string to an integer
        int value = std::stoi(segment);
        if (value > 255) {
            return false;
        }

        return true;
    }
};

// Helper function to print results
void printResult(std::string s, const std::vector<std::string>& result) {
    std::cout << "Input: \"" << s << "\"\nResult: [";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "\"" << result[i] << "\"" << (i < result.size() - 1 ? ", " : "");
    }
    std::cout << "]\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Standard case
    std::string s1 = "25525511135";
    printResult(s1, solver.restoreIpAddresses(s1));

    // Test Case 2: Lots of zeros (tests the leading zero logic)
    std::string s2 = "0000";
    printResult(s2, solver.restoreIpAddresses(s2));

    // Test Case 3: A mix that requires exploring multiple bounds
    std::string s3 = "101023";
    printResult(s3, solver.restoreIpAddresses(s3));

    // Test Case 4: Invalid string (too long)
    std::string s4 = "1111111111111"; // 13 chars
    printResult(s4, solver.restoreIpAddresses(s4));

    return 0;
}
