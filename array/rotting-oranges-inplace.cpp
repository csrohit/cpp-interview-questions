/*
 * ============================================================================
 * LEETCODE 994: ROTTING ORANGES (DISTANCE MAP APPROACH)
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - In-place Grid Modification: Repurposing the input grid to save space, 
 * using it to store the "Minute of Infection" for each cell.
 * - Operator Precedence: Understanding that `&&` evaluates before `||`, 
 * requiring explicit structure in boundary checks.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Transform the grid. 2 -> 0, 1 -> INT_MAX, 0 -> -1.
 * Step 2: Push all initial rotten oranges (now 0) into `rottenQueue`.
 * Step 3: While the queue is not empty, pop an orange and get its `timeOfInfection`.
 * Step 4: Check all 4 neighbors. If out of bounds or -1, skip.
 * Step 5: If the neighbor's current value is > `timeOfInfection + 1`, update it, 
 * decrement the fresh count, update `maxMinutesElapsed`, and push to queue.
 * Step 6: Return `maxMinutesElapsed` if `nFreshOranges` == 0, else return -1.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

class Solution {
public:
    /**
     * @brief Finds the minimum time to rot all oranges using an in-place Distance Map.
     * Complexity Analysis:
     * - Time: O(R * C). Every cell is processed and updated at most once.
     * - Space: O(R * C). The queue may store all oranges in the worst case.
     */
    int orangesRotting(std::vector<std::vector<int>>& grid) {
        if (grid.empty()) return 0;

        std::queue<std::pair<int, int>> rotten;
        int nRows = (int)grid.size();
        int nCols = (int)grid[0].size();
        int nFreshOranges = 0;
        int maxMinutesElapsed = 0;

        // Step 1: Initial Grid Transformation
        for (int idx = 0; idx < nRows; ++idx) {
            for (int jdx = 0; jdx < nCols; ++jdx) {
                if (grid[idx][jdx] == 2) {
                    grid[idx][jdx] = 0; // Rot starts at Minute 0
                    rotten.push({idx, jdx});
                } else if (grid[idx][jdx] == 1) {
                    grid[idx][jdx] = INT_MAX; // Fresh = Infinity
                    nFreshOranges++;
                } else {
                    grid[idx][jdx] = -1; // Empty = Blocked
                }
            }
        }

        if (nFreshOranges == 0) return 0;

        // Directions: Up, Down, Left, Right
        std::vector<std::pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // Step 2: Spreading the Rot
        while (!rotten.empty()) {
            std::pair<int, int> currentPos = rotten.front();
            rotten.pop();

            // The time of the orange CURRENTLY spreading the rot
            int timeOfInfection = grid[currentPos.first][currentPos.second];

            for (const std::pair<int, int>& dir : dirs) {
                int neighbourRow = currentPos.first + dir.first;
                int neighbourCol = currentPos.second + dir.second;

                // Explicit bounds check using separate || conditions
                if (neighbourRow < 0 || neighbourRow >= nRows || 
                    neighbourCol < 0 || neighbourCol >= nCols) {
                    continue;
                }
                
                // If it's an empty cell (blocked), skip
                if (grid[neighbourRow][neighbourCol] == -1) {
                    continue;
                }

                // Check if current infection path is faster than neighbor's state
                if (grid[neighbourRow][neighbourCol] > timeOfInfection + 1) {
                    
                    grid[neighbourRow][neighbourCol] = timeOfInfection + 1;
                    nFreshOranges--;
                    rotten.push({neighbourRow, neighbourCol});
                    maxMinutesElapsed = std::max(maxMinutesElapsed, grid[neighbourRow][neighbourCol]);
                }
            }
        }

        return (nFreshOranges == 0) ? maxMinutesElapsed : -1;
    }
};

// Helper function to print results
void printResult(std::vector<std::vector<int>> grid, int expected) {
    Solution solver;
    int result = solver.orangesRotting(grid);
    std::cout << "Expected: " << expected << " | Result: " << result;
    if (result == expected) {
        std::cout << " [PASS]\n";
    } else {
        std::cout << " [FAIL]\n";
    }
}

int main() {
    // Test Case 1: Standard scenario (Takes 4 minutes)
    std::vector<std::vector<int>> grid1 = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };
    printResult(grid1, 4);

    // Test Case 2: Unreachable orange (Should return -1)
    std::vector<std::vector<int>> grid2 = {
        {2, 1, 1},
        {0, 1, 1},
        {1, 0, 1}
    };
    printResult(grid2, -1);

    // Test Case 3: Already fully rotten/empty (Takes 0 minutes)
    std::vector<std::vector<int>> grid3 = {
        {0, 2}
    };
    printResult(grid3, 0);

    return 0;
}
