#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

class Solution
{

public:
    void reverseStrong(vector<char> &s)
    {
        vector<char>::iterator start = s.begin(), end = s.end();
        while (start < end)
        {
            char temp = *start;
            *start++ = *end;    
            *end-- = temp;
        }
    }
};

int main(){
    Solution s;
    char str[] = "time command in Linux is used to execute a command and prints a summary of real-time, user CPU time and system CPU time spent by executing a command when it terminates. ‘real‘ time is the time elapsed wall clock time taken by a command to get executed, while ‘user‘ and ‘sys‘ t";
    vector<char> v (str, str + strlen(str));
    s.reverseStrong(v);
    for (char i: v)
    std::cout << i;
    // const char * const str = "rohit";




    return 0;
}