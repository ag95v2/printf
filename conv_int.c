
/*
**	Here you can find declarations of integer conversion functions
*/

#include "printf.h"
#include "libft.h"

char	*itoa_b10u(long long n)
{
	return (ft_itoa_base(n, 10));
}

char	*itoa_b10(long long n)
{
	return (ft_itoa_base(n, 10));
}

char	*itoa_b2(long long n)
{
	return (ft_itoa_base(n, 2));
}

char	*itoa_b8(long long n)
{
	return (ft_itoa_base(n, 8));
}

char	*itoa_bX(long long n)
{
	return (ft_itoa_base(n, 16));
}

char        *ft_itoa_base(long long value, int base)
{
    char    *s;
    int     len;
    unsigned long long value1;

    value1 = (unsigned long long)value;
    if (value1 == 0)
        return (ft_strdup("0"));
    if (base < 2 || base > 16)
        return (NULL);
    len = ft_num_len(value1, base);
    if (!(s = ft_strnew(len + 1)))
        return (NULL);
    s[len] = '\0';
    while (len-- > 0)
    {
       s[len] = (value1 % base < 10) ? value1 % base + '0' : value1 % base + 'a' - 10;
       value1 /= base;
    }
    return (s);
}
