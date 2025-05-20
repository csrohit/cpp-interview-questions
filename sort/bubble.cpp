#include <cstdio>
#include <vector>

using namespace std;

void printArray(vector<int> &arr)
{
    for (int i : arr)
    {
        printf("%-4d", i);
    }
    printf("\n");
}

void sort(vector<int> &arr)
{
    int size = arr.size();
    for (int idx = 0; idx < size; ++idx)
    {
        for (int jdx = 0; jdx < size - idx - 1; ++jdx)
        {
            if (arr[jdx] > arr[jdx + 1])
            {
                swap(arr[jdx], arr[jdx + 1]);
            }
        }
    }
}

int main()
{

    vector arr = {5, 8, 3, 7, 9, 2, 6, 1, 4};
    printArray(arr);
    sort(arr);
    printArray(arr);

    return 0;
}
