#include "libft.h"

int         ft_num_len(long long num, int base)
{
    int     i;

    i = 0;
    if (num < 0)
        i++;
    while (num > 0)
    {
        num = num / base;
        i++;
    }
    return (i);
}
