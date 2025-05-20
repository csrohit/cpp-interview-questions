#include <stdint.h>
#include <stdio.h>

#define SIZE_OF(x) (((uint8_t *)(&x + 1)) - ((uint8_t *)(&x)))
#define SIZE_TF(x) ((size_t)((x *)0 + 1))

struct abc
{
    int   a;
    void *b;
};

int main()
{

    long int a = 10;
    printf("Size of a = %ld\n", SIZE_TF(struct abc));

    return 0;
}
