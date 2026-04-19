/*
 * ============================================================================
 * LEETCODE 207: COURSE SCHEDULE (READABLE VARIABLES)
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - Topological Sort (Kahn's Algorithm): Resolving a chain of dependencies 
 * by continually processing items that have zero remaining blockers.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Setup `dependents` to map `prerequisite -> [dependent courses]`.
 * Step 2: Setup `prereqCount` to tally how many blockers a course has.
 * Step 3: Populate both structures using the `prerequisites` pairs.
 * Step 4: Scan `prereqCount`. Push any course with `0` blockers into the 
 * `readyCourses` queue.
 * Step 5: Loop while `readyCourses` has classes to take.
 * Step 6: Pop the `currentCourse` and increment `passedCount`.
 * Step 7: Iterate through the `dependents` of the `currentCourse`. Decrement 
 * their `prereqCount` because we just cleared a hurdle for them.
 * Step 8: If a `dependentCourse`'s `prereqCount` drops to `0`, push it to the queue.
 * Step 9: Return true if `passedCount == numCourses`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>

class Solution {
public:
    /**
     * @brief Determines if all courses can be finished without getting stuck in a cycle.
     * Complexity Analysis:
     * - Time: O(V + E). V = numCourses, E = length of prerequisites.
     * - Space: O(V + E). The dependents list stores every connection.
     */
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        
        // dependents[i] holds a list of all courses that CANNOT be taken until 'i' is passed
        std::vector<std::vector<int>> nextCourses(numCourses);
        
        // prereqCount[i] holds the number of classes blocking course 'i'
        std::vector<int> prereqCount(numCourses, 0);

        // Populate our relationship mappers
        for (const auto& pair : prerequisites) {
            int course = pair[0];
            int prereq = pair[1];
            
            nextCourses[prereq].push_back(course);
            prereqCount[course]++;
        }

        // Find courses we can take on day one
        std::queue<int> readyCourses;
        for (int i = 0; i < numCourses; ++i) {
            if (prereqCount[i] == 0) {
                readyCourses.push(i);
            }
        }

        int passedCount = 0;

        // Process our course load
        while (!readyCourses.empty()) {
            int currentCourse = readyCourses.front();
            readyCourses.pop();
            passedCount++;

            // Unlock the courses that were waiting on us
            for (int dependentCourse : nextCourses[currentCourse]) {
                prereqCount[dependentCourse]--;

                // If the dependent course is now fully unlocked, queue it
                if (prereqCount[dependentCourse] == 0) {
                    readyCourses.push(dependentCourse);
                }
            }
        }

        // Did we successfully take everything without hitting a cycle?
        return passedCount == numCourses;
    }
};

// Helper function to print results
void printResult(int numCourses, const std::vector<std::vector<int>>& prerequisites, bool expected, bool result) {
    std::cout << "Courses: " << numCourses << " | Prerequisites: [";
    for (size_t i = 0; i < prerequisites.size(); ++i) {
        std::cout << "[" << prerequisites[i][0] << "," << prerequisites[i][1] << "]" << (i < prerequisites.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";
    std::cout << "Expected: " << (expected ? "True" : "False") 
              << " | Result: " << (result ? "True" : "False") << "\n\n";
}

int main() {
    Solution solver;

    // Test Case 1: Simple linear path (1 requires 0)
    std::vector<std::vector<int>> prereq1 = {{1, 0}};
    printResult(2, prereq1, true, solver.canFinish(2, prereq1));

    // Test Case 2: Impossible Cycle (1 requires 0, 0 requires 1)
    std::vector<std::vector<int>> prereq2 = {{1, 0}, {0, 1}};
    printResult(2, prereq2, false, solver.canFinish(2, prereq2));

    return 0;
}
