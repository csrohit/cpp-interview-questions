#include<cstdio>
#include <unordered_set>
#include <vector>

//C++ program to find the length of the longest consecutive sequence in an array
// Input: 2, 6, 1, 9, 4, 5, 3,
// Output: 6

int longestSubsequence(std::vector<int>& nums)
{
    if (nums.empty())
    {
        return 0;
    }

    int maxlen = 1;

    /* Create unordered_set from nums */
    std::unordered_set<int> set(nums.begin(), nums.end());

    for (int num: nums)
    {
        if (set.find(num - 1) == set.end())
        {
            int current_num = num;
            int currentLongest = 1;

            while(set.count(current_num + 1) > 0)
            {
                current_num++;
                currentLongest++;
            }

            if (maxlen < currentLongest)
            {
                maxlen = currentLongest;
                if (maxlen > nums.size() / 2)
                {
                    break;
                }
            }
        }
    }

    return maxlen;
}

int main()
{
    std::vector<int> nums{2, 6, 1, 9, 4, 5, 3};

    printf("Length of longest consecutive subsequence: %d\n", longestSubsequence(nums));
    return 0;
}
