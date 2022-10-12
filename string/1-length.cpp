#include <iostream>

using namespace std;

/**
 * @brief Get the length string
 * 
 * @param p_str pointer to string
 * @return size_t length of string
 */
size_t get_length(const char *p_str);

int main()
{
    cout << get_length("Sample string") << endl;
    return 0;
}

size_t get_length(const char *p_str)
{
    size_t length = 0;
    while (*(p_str + length))
        length++;
    return length;
}