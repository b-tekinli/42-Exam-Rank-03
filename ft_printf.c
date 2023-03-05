#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int ft_putstr(char *str)
{
    int count = 0;
    if(!str)
    {
        count += write(1, "(null)", 6);
        return(count);
    }
    while(*str)
        count += write(1, str++, 1);
    return(count);
}

int ft_putnbr(long num, int base)
{
    int count = 0;
    if(num < 0)
    {
        num *= -1;
        count += write(1, "-", 1);
    }
    if(num > (base - 1))
        count += ft_putnbr(num/base, base);
    count += write(1, &"0123456789abcdef"[num % base], 1);
    return(count);
}

int ft_printf(const char *str, ...)
{
    int count = 0;
    va_list list;
    va_start(list, str);
    while(*str)
    {
        if(*str == '%')
        {
            str++;
            if(*str == 's')
                count += ft_putstr(va_arg(list, char*));
            else if(*str == 'd')
                count += ft_putnbr(va_arg(list, int), 10);
            else if(*str == 'x')
                count += ft_putnbr(va_arg(list, unsigned int), 16);
        }
        else 
            count += write(1, str, 1);
            str++;
    }
    return(count);
}

int main()
{
    ft_printf("%x", 17);
}