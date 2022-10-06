#include<iostream>

using namespace std;

int main(){

    int a[] = {1,2,3,4,5,6};
    char str[] = "Hellow";
    cout << a[0];

    // here a and str are addresses of array and hence cannot be modified, compiler throws error
    a++;
    str++;
    cout << a[0];
    return 0;
}