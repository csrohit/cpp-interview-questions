#include <iostream>
#include <cstring>

using namespace std;
/**
 * @brief Get the length string
 * 
 * @param p_str pointer to string
 * @return size_t length of string
 */
size_t get_length(const char *p_str);

/**
 * @brief Copy source string into destination string
 *
 * @param p_dest sufficiently large space for source string
 * @param p_src pointer to source string
 * @return ssize_t no. of characters copied
 */
ssize_t cpy(char *p_dest, const char *p_src);

int main()
{
    const char * p_src = "src str";
    char name[20]= "This destination.";
    cout<< "Source: "<< p_src << endl;
    cout << "Dest: "<< name << endl;
    cpy(name, p_src);
    cout << "After copy => \nDest: " << name << endl;
}

size_t get_length(const char *p_str)
{
    size_t length = 0;
    while (*(p_str + length))
        length++;
    return length;
}

ssize_t cpy(char *p_dest, const char *p_src)
{
    if(p_src == NULL || p_dest == NULL)
    return -1;

    ssize_t len = 0;
    while (*(p_src + len))
    {   
        // right to left execution of statement, i.e. RHS is evaluated first then LHS
        *(p_dest + len++) = *(p_src + len);
        // *(p_dest + len) = *(p_src + len++); => replace 1st char of source to 2nd char of dest
    }
    return len;
}