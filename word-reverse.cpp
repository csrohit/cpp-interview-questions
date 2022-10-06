#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

/**
 * @brief Reverses the word in place    
 * 
 * @param start address of start of string
 * @param len length of string
 */
void reverse_word(char * start, int len){
    int i=0;
    char c;
    while(i < --len){
        c = *(start + i);
        *(start + i++) = *(start + len);
        *(start + len) = c;
    }
}

/**
 * @brief Reverses order of words of string
 * 
 * @param str pointer to string
 */
void reverse(char * str){
    int len=0, pos=0;

    while (*(str + pos))
    {
        // skip non string characters
        len = strspn(str + pos, " \t\n\r");
        pos += len;

        // count length of first word
        len = strcspn(str + pos, " \t\n\r");
        reverse_word(str + pos, len);
        pos += len;
    }

    reverse_word(str, pos);
}

int main()
{

    char str[] = "The sky is blue";
    printf("Entered string: %s\n", str);
    reverse(str);
    printf("Revered word order: %s\n", str);
    return 0;
}
