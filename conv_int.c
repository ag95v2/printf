
/*
**	Here you can find declarations of integer conversion functions
*/

#include "printf.h"
#include "libft/includes/libft.h"

char	*itoa_b10u(long long n)
{
	if (n < 0)
		n = n * (-1);
	return (ft_itoa_base(long long n, 10));
}

char	*itoa_b10(long long n)
{
	// Your code here
	// Convert long long to string base 10
	return (ft_itoa_base(long long n, 10));
}

char	*itoa_b2(long long n)
{
	// Your code here
	// Convert long long to string base 2
	return (ft_itoa_base(long long n, 2));
}

char	*itoa_b8(long long n)
{
	// Your code here
	// Convert long long to string base 8
	return (ft_itoa_base(long long n, 8));
}

char	*itoa_bX(long long n)
{
	// Your code here
	// Convert long long to string base hex in uppercase
	return (ft_itoa_base(long long n, 16));
}

char	*itoa_bx(long long value)
{
    char    *s;
    int     len;
	int		base;

	base = 16;
    if (value == 0)
        return (ft_strdup("0"));
    if (base < 2 || base > 16)
        return (NULL);
    if (value == -2147483648 && base == 10)
        return (ft_strdup("-2147483648"));
    len = ft_num_len(value, base);
    if (!(s = ft_strnew(len + 1)))
        return (NULL);
    if (value < 0)
    {
        s[0] = '-';
        value = value * (-1);
    }
    s[len] = '\0';
    while (len-- > 0)
    {
       s[len] = (value % base < 10) ? value % base + '0' : value % base + 'a' - 10;
       value /= base;
    }
    return (s);
}
