#include "libft.h"

/*
 **if other number with minus, we are changing to positive
 **and plus 1 to i, than to take account a minus in our string
*/

int         ft_num_len(int num, int base)
{
    int     i;

    i = 0;
    if (num < 0)
    {
        num = num * (-1);
        i++;
    }
    while (num > 0)
    {
        num = num / base;
        i++;
    }
    return (i);
}

/*
 * -at first we are checking our number with other terms.
 * -note that min int number term is actuall just if base == 10
 * -we are finding discharge of number than to know how many
 * memory should to allocate memory to our string
 * -in cycle we are starting from the end
 *  checking via terminate operator if base is smaller than 10, we don't use letters
 *  therefore starting filling via end of number. 
 *  But if base is more than 10, we are using letters. 
 *  -10 after 'A' because max base is 16 and as a rules we could use just to letter
 *  'F'
*/

char        *ft_itoa_base(long long value, int base)
{
    char    *s;
    int     len;

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
       s[len] = (value % base < 10) ? value % base + '0' : value % base + 'A' - 10;
       value /= base;
    }
    return (s);
}
