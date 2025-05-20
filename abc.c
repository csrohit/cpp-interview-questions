#include <stdint.h>

int main()
{

    uint32_t regA;
    uint32_t regB;

    int mA, nB;

    // read bit from A
    uint32_t tmp = (regA >> mA) & 0x01;
    uint32_t tmpB = (regB >> nB) & 0x01;

    // clear bits
    regA = regA & ~ (1 << mA);
    regB = regB & ~ (1 << nB);

    regA = regA | (tmpB << mA); 
    regB = regB | (tmp << nB); 



    return (0);
}


