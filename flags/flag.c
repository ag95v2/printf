#include <stdlib.h>
#include "printf.h"

char        *ft_print_flags(t_spec *spec, double num, char *string)
{
    char    *str;
    t_spec  a;

    if(!(str = strnew(5)))
        return (NULL);
    if (a.flag_plus == 1 && num > 0)
        str[1] = '+';
    if (a.flag_space == 1)

}