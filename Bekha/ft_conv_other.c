#include "ft_printf.h"

char    ctoa(char c)
{
    char    res[2];

    res[0] = c;
    res[1] = '\0';
    return (&res);    
}

char    *stoa(char *s)
{
    return (s);
}



char    *percent_to_a(void)
{
    char     c[2];

    c[0] = '%';
    c[1] = '\0';
    return (&c);
}

char    *binoa(char c)
{
    
}