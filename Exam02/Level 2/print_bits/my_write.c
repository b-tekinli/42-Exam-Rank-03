#include <stdio.h>

void print_bits(unsigned char octet)
{
    int i;
    for (i = 7; i >= 0; --i)
    {
        if ((octet >> i) & 1)
            putchar('1');
        else
            putchar('0');
    }
}

/*

int main()
{
    unsigned char my_byte = 2;  // 00000010
    print_bits(my_byte);        // "00000010" çıktısını verir
}

*/
