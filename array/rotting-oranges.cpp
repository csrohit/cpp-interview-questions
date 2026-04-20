/*
 * ============================================================================
 * LEETCODE 994: ROTTING ORANGES
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Multi-Source BFS: Starting a search from multiple nodes simultaneously 
 * to find the shortest time to reach all other reachable nodes.
 * - Layer-by-layer processing: Using the size of the queue to process all 
 * nodes at "Distance T" before moving to "Distance T+1".
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Scan the grid. Count fresh oranges and add initial rotten orange 
 * coordinates to `rottenQueue`.
 * Step 2: Use a `while` loop that runs as long as the queue isn't empty and 
 * there are still fresh oranges to rot.
 * Step 3: Inside the loop, increment `minutesElapsed`. 
 * Step 4: Capture the `currentQueueSize`. Process exactly that many oranges.
 * Step 5: For each orange, check its 4 neighbors. If a neighbor is fresh, 
 * change it to rotten, decrement `freshOrangeCount`, and add it to the queue.
 * Step 6: After the loop, if `freshOrangeCount` is 0, return the time. 
 * Otherwise, return -1.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - BFS Level Tracking: By using `currentQueueSize` inside the while loop, 
 * we ensure that one iteration of the while loop corresponds to exactly 
 * one minute of real-time spreading.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>

class Solution {
public:
    /**
     * @brief Calculates the minimum minutes until no cell has a fresh orange.
     * Complexity Analysis:
     * - Time: O(R * C). We visit every cell in the grid at most twice.
     * - Space: O(R * C). In the worst case, the queue stores all oranges.
     */
    int orangesRotting(std::vector<std::vector<int>>& grid) {
        int rows = (int)grid.size();
        int cols = (int)grid[0].size();
        
        std::queue<std::pair<int, int>> rottenQueue;
        int freshOrangeCount = 0;

        // Step 1: Initialize the state
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 2) {
                    rottenQueue.push({r, c});
                } else if (grid[r][c] == 1) {
                    freshOrangeCount++;
                }
            }
        }

        // If there are no fresh oranges, 0 minutes are needed.
        if (freshOrangeCount == 0) return 0;

        int minutesElapsed = 0;
        
        // Directions for Up, Down, Left, Right
        std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // Step 2: Multi-source BFS
        while (!rottenQueue.empty() && freshOrangeCount > 0) {
            minutesElapsed++;
            
            // Process all oranges that are currently rotten (this level)
            int currentQueueSize = (int)rottenQueue.size();
            
            for (int i = 0; i < currentQueueSize; ++i) {
                std::pair<int, int> currentPos = rottenQueue.front();
                rottenQueue.pop();

                int currentRow = currentPos.first;
                int currentCol = currentPos.second;

                // Check all 4 neighbors
                for (const std::pair<int, int>& dir : directions) {
                    int neighborRow = currentRow + dir.first;
                    int neighborCol = currentCol + dir.second;

                    // Check bounds and if the orange is fresh
                    if (neighborRow >= 0 && neighborRow < rows && 
                        neighborCol >= 0 && neighborCol < cols && 
                        grid[neighborRow][neighborCol] == 1) {
                        
                        // Rot the orange
                        grid[neighborRow][neighborCol] = 2;
                        freshOrangeCount--;
                        rottenQueue.push({neighborRow, neighborCol});
                    }
                }
            }
        }

        // Step 3: Final check
        return (freshOrangeCount == 0) ? minutesElapsed : -1;
    }
};

int main() {
    Solution solver;
    
    // Test Case: Standard scenario
    // [[2,1,1],[1,1,0],[0,1,1]]
    std::vector<std::vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    std::cout << "Minutes to rot all: " << solver.orangesRotting(grid) << " (Expected: 4)" << std::endl;

    return 0;
}
