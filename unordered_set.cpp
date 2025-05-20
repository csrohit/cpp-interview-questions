#include<cstdio>
#include <unordered_set>



int main()
{
    std::unordered_set<int> seen;

    seen.insert(10);
    seen.insert(11);
    seen.insert(12);
    seen.insert(10);
    printf("Size of seen: %lu\n", seen.size());
}
