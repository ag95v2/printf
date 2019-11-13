#include "libft.h"

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
       s[len] = (value1 % base < 10) ? value1 % base + '0' : value1 % base + 'A' - 10;
       value1 /= base;
    }
    return (s);
}
