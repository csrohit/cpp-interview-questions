#include <cstdio>
#include <cstdint>

int clz(uint32_t number)
{
    int count = 0;

    if ((0XFFFF0000 & number) == 0)
    {
        count += 16;
    }
    else
    {
        number = number >> 16;
    }

    if ((0XFF00 & number) == 0)
    {
        count += 8;
    }
    else
    {
        number = number >> 8;
    }

    if ((0XF0 & number) == 0)
    {
        count += 4;
    }
    else
    {
        number = number >> 4;
    }

    if ((0XC & number) == 0)
    {
        count += 2;
    }
    else
    {
        number = number >> 2;
    }

    if ((0X2 & number) == 0)
    {
        count += 1;
    }
    else
    {
        number = number >> 1;
    }

    if ((0X1 & number) == 0)
    {
        count += 1;
    }

    return count;
}

int main()
{
    uint32_t n = 4;

    printf("Number of leading zeroes for %u -> %d\n", n, clz(n));

    return (0);
}
