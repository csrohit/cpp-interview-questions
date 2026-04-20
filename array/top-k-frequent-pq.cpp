/*
 * ============================================================================
 * LEETCODE 347: TOP K FREQUENT ELEMENTS (MIN-HEAP APPROACH)
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - std::priority_queue: A container that provides O(log n) insertion and 
 * O(1) access to the top element. By using `std::greater`, it becomes a 
 * Min-Heap (smallest value at the top).
 * - Pair Comparison: In C++, comparing `std::pair<int, int>` compares the 
 * first element first. We store frequency first so the heap sorts by frequency.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Count occurrences of each number in `numToFrequency`.
 * Step 2: Create a `minHeap` that stores pairs of `{frequency, value}`.
 * Step 3: Iterate through the map. For every number, push it into the heap.
 * Step 4: Immediately check if `minHeap.size() > k`. If it is, `pop()`. 
 * This keeps the heap size small and ensures only the highest frequencies stay.
 * Step 5: Transfer the remaining `k` values from the heap to the `result` vector.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Time Complexity: O(n log k). Inserting into a heap of size k takes log(k). 
 * We do this n times.
 * - Space Complexity: O(n + k). We store the map (n) and the heap (k).
 * ============================================================================
 */

#include <vector>
#include <unordered_map>
#include <queue>

class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        
        // Step 1: Count frequencies
        std::unordered_map<int, int> numToFrequency;
        for (int num : nums) {
            numToFrequency[num]++;
        }

        // Step 2: Define a Min-Heap of pairs {frequency, value}
        // std::greater tells the queue to keep the SMALLEST frequency at the top
        typedef std::pair<int, int> FreqPair;
        std::priority_queue<FreqPair, std::vector<FreqPair>, std::greater<FreqPair>> minHeap;

        // Step 3: Iterate through the map entries
        for (const std::pair<const int, int>& entry : numToFrequency) {
            int value = entry.first;
            int frequency = entry.second;

            // Push {frequency, value}
            minHeap.push({frequency, value});

            // If we have more than k elements, kick out the least frequent one
            if (minHeap.size() > (size_t)k) {
                minHeap.pop();
            }
        }

        // Step 4: Extract the values from the heap
        std::vector<int> topKValues;
        while (!minHeap.empty()) {
            // We want the 'second' part of the pair (the actual number)
            topKValues.push_back(minHeap.top().second);
            minHeap.pop();
        }

        return topKValues;
    }
};
