/*
 * ============================================================================
 * LEETCODE 207: COURSE SCHEDULE (DFS CYCLE DETECTION)
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Depth-First Search (DFS): Recursively exploring a graph by going as deep 
 * as possible along each branch before backtracking.
 * - 3-State Cycle Detection: Using an Enum to distinctly track nodes we haven't 
 * seen, nodes we are actively exploring, and nodes we have completely verified.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Define an `enum State` for `NotVisited`, `InProgress`, and `Visited`.
 * Step 2: Initialize a `state` vector of size `numCourses` to `NotVisited`.
 * Step 3: Build the adjacency list `adj`. The relationship is `target -> pre`, 
 * meaning the advanced course points to what it requires.
 * Step 4: Loop through every course from `0` to `numCourses - 1`.
 * Step 5: For each course, call `dfs()`. If it ever returns false, a cycle 
 * exists. Return false immediately.
 * Step 6: Inside `dfs()`, check the base cases: If the course is `InProgress`, 
 * a cycle is caught (return false). If it is `Visited`, use memoization to 
 * skip redundant work (return true).
 * Step 7: Mark the current course as `InProgress`.
 * Step 8: Recursively call `dfs()` on all of its prerequisites.
 * Step 9: If all prerequisites clear, mark the course as `Visited` and return true.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Self-Documenting Code: By using an `enum` instead of magic numbers (0, 1, 2), 
 * the base cases (`InProgress == state[course]`) read exactly like human logic. 
 * - Memory Efficiency: Using `const auto&` in the setup loop prevents the C++ 
 * compiler from making thousands of expensive, hidden vector copies.
 * ============================================================================
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // LeetCode guarantees at most 2000 courses, so 2005 is a safe fixed buffer.
    vector<int> adj[2005];
    
    enum State
    {
        NotVisited = 0,
        InProgress = 1,
        Visited = 2
    };

    bool dfs(vector<State>& state, int course)
    {
        if (InProgress == state[course])
        {
            return false; //
