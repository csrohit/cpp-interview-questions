#include <bits/stdc++.h>

using namespace std;

vector<int> diagonal(vector<vector<int>> &mat)
{

    int n_row = mat.size(), n_col = mat[0].size();
    vector<int> ret;
    int x = 0, y = 1;

    int isUp = 0;
    int to_be_visited = n_row * n_col;
    ret.push_back(mat[0][0]);
    to_be_visited--;

    while (to_be_visited)
    {
        ret.push_back(mat[x][y]);
        if (isUp)
        {

            if (x == 0 || y == n_col - 1)
            {
                isUp = 0;
                if (y == n_col - 1)
                {
                    x++;
                }
                if (x == 0)
                {
                    y++;
                }
            }
            else
            {
                y++;
                x--;
            }
        }
        else
        {
            if (x == n_row - 1 || y == 0)
            {
                isUp = 1;
                if (x == n_row - 1)
                {
                    y++;
                }
                if (y == 0)
                {
                    x++;
                }
            }
            else
            {
                x++;
                y--;
            }
        }
        to_be_visited--;
    }
    return ret;
}

int main()
{

    vector<vector<int>> a{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16},
        {17,18,19,20}};

    for (int i : diagonal(a))
    {
        printf("%-4d", i);
    }
    cout << endl;
    return 0;
}