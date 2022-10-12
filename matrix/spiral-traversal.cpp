#include<bits/stdc++.h>
using namespace std;

vector<int> spiralOrder(vector<vector<int>> &a){
    int nRow = a.size();
    int nCol = a[0].size();
    vector<int> ret;

    if(nRow == 0){
        return ans;
    }

    

    for (int i = 0; i < nRow*nCol -1; i++)
    {
        ret.push_back(a[i]);
    }
    

    return ret;
}

int main(){

    vector<vector<int>> a{
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };

    return 0;
}