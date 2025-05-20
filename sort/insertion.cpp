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
    for (int idx = 1; idx < size; ++idx)
    {
        int key = arr[idx];
        int j = idx - 1;
        while ((0 <= j) && (arr[j] > key))
        {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
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
