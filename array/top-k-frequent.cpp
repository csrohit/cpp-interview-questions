/*
 * ============================================================================
 * LEETCODE 347: TOP K FREQUENT ELEMENTS
 * ============================================================================
 *
 * 1. PRE-REQUISITES / CONCEPTS:
 * -----------------------------
 * - std::unordered_map: For O(1) average time complexity frequency counting.
 * - Bucket Sort: Using an array's indices to represent frequencies. This 
 * avoids the O(n log n) cost of sorting the frequencies themselves.
 *
 * 2. STEPS TO SOLVE:
 * ------------------
 * Step 1: Count occurrences of each number in `frequencyMap`.
 * Step 2: Create a `buckets` vector of vectors. The outer vector's index 
 * represents the "Frequency".
 * Step 3: Iterate through the map. Place each number into `buckets[frequency]`.
 * Step 4: Iterate through the buckets array from right-to-left (highest 
 * frequency to lowest).
 * Step 5: Append numbers to the `result` vector until the size is exactly `k`.
 *
 * 3. KEY TAKEAWAYS:
 * -----------------
 * - Explicit Types: Using `std::pair<const int, int>` when iterating over a 
 * map clarifies that the key is constant and the value is the count.
 * - Why Bucket Sort? A standard sort on frequencies is O(N log N). Since 
 * frequencies are bounded by the size of the input array [0, N], we can use 
 * the index-as-value trick to reach O(N).
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    /**
     * @brief Finds the k most frequent elements using Bucket Sort.
     * Complexity Analysis:
     * - Time: O(n). One pass to count, one pass to bucket, and one pass to gather.
     * - Space: O(n). To store the frequency map and the buckets.
     */
    std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
        
        // Step 1: Count the frequency of each number
        std::unordered_map<int, int> frequencyMap;
        for (int num : nums) {
            frequencyMap[num]++;
        }

        // Step 2: Create buckets where index is the frequency
        // Size is nums.size() + 1 to handle the case where a number appears 'n' times
        std::vector<std::vector<int>> buckets(nums.size() + 1);
        
        // Iterating through the map without 'auto'
        // A map stores std::pair<const Key, Value>
        for (const std::pair<const int, int>& entry : frequencyMap) {
            int value = entry.first;
            int frequency = entry.second;
            
            buckets[frequency].push_back(value);
        }

        // Step 3: Collect the top K frequent elements
        std::vector<int> topElements;

        // Iterate backwards from the max possible frequency
        for (int f = (int)buckets.size() - 1; f >= 0; --f) {
            const std::vector<int>& currentBucket = buckets[f];
            
            for (int num : currentBucket) {
                topElements.push_back(num);
                
                // Once we have k elements, we stop immediately
                if (topElements.size() == (size_t)k) {
                    return topElements;
                }
            }
        }

        return topElements;
    }
};

int main() {
    Solution solver;
    std::vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;

    std::vector<int> result = solver.topKFrequent(nums, k);

    std::cout << "Top " << k << " frequent elements: ";
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl; // Expected: 1 2

    return 0;
}
