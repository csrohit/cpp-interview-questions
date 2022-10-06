#include<iostream>
#include<cstring>

using namespace std;

int main(){
    // cannot use char * as the string is stored in .rodata section and cannot be modified
    char str[] = "time command in Linux is used to execute a command and prints a summary of real-time, user CPU time and system CPU time spent by executing a command when it terminates. ‘real‘ time is the time elapsed wall clock time taken by a command to get executed, while ‘user‘ and ‘sys‘ t";
    char temp;
    ssize_t length = strlen(str)- 1;
    std::cout << "Original string is: " << str << endl;

    //! normal method
    // for (uint16_t i = 0; i <= length/2; i++)
    // {
    //     temp = str[i];
    //     str[i] = str[length -i];
    //     str[length -i] = temp;
    // }

    //? 2 pointer approach faster than loop method
    char *left = str, *right = str + length;
    while (str != right)
    {
        char temp =  *left;
        *left++ = *right;
        *right-- = temp;
    }
    
    std::cout << "Reversed string is: " << str << endl ;
    return 0;
}