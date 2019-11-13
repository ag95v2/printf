#include "libft.h"

int         ft_num_len(unsigned long long num, int base)
{
    int     i;

    i = 0;
    while (num > 0)
    {
        num = num / base;
        i++;
    }
    return (i);
}
