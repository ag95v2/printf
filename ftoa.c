#include <stdio.h>
#include <stdlib.h>
#include "printf.h"

typedef struct variablesforfloat
{
    char                *string;
    long long           integer;
    long double         fractional;
    long long           cp_integer;
    long double         cp_fractional;
    int                 sym;
    long double         tmp;
    long long           lenbef;
    long long           lenaf;
    long long           cp_lenbef;
    long long           cp_lenaf;    
    int                 i;
    int                 tmp2;
    int                 number;
    int                 p;
    char                *res;
}                       varfloat;

int	ft_inter_len(long long inter)
{
	int				i;

	i = 0;
	if (inter <= 0)
	{
		inter = inter * (-1);
		i++;
	}
	while (inter > 0)
	{
		inter = inter / 10;
		i++;
	}
	return (i);
}

/*
** Than to fill string with fractional numbers;
*/

char        *f_fill_fractional(varfloat *f)
{
    f->i = 0;
    (f->fractional < 0) ? f->fractional *= -1 : 0;
    while (f->i < 40)
    {
        f->fractional *= 10;
        f->tmp2 = (int)f->fractional;
        f->string[f->lenaf++] = f->tmp2 + '0';
        f->fractional = f->fractional - f->tmp2;
        f->i++;
    }
    return (f->string);
}

/*
** for integer = 0 and some numbers in fracitonal
*/

char        *f_fill_zero_fractional(varfloat *f)
{
    if (f->fractional < 0)
    {
        f->string[0] = '-';
        f->string[f->lenbef] = '0';
        f->string[f->lenbef + 1] = '.';
        f->lenaf++;
    }
    else
        f->string[f->lenbef - 1] = '0';
    return (f_fill_fractional(f));
}

/*
**  Our goal fill the string if input number less than 0;
**  taking module of numbers;
**  Put dot; Put minus;
**  In cycle adding ever number to our string
**  through receiving the remainder;
**  After filling integer with minus filling fractional of
**  number.
*/

char        *f_fill_integer_min(varfloat *f)
{
    if (f->integer == 0 && f->fractional < 0)
        return (f_fill_zero_fractional(f));
    else
    {
        f->string[f->lenbef--] = '.';
        f->string[0] = '-';
    }
    
    f->integer *= -1;
    while (0 < f->lenbef)
    {
        f->string[f->lenbef--] = f->integer % 10 + '0';
        f->integer /= 10;
    }
    return (f_fill_fractional(f));
}

char        *f_fill_integer(varfloat *f)
{
    f->string[f->lenbef--] = '.';
    while (0 <= f->lenbef)
    {
        f->string[f->lenbef--] = f->integer % 10 + '0';
        f->integer /= 10;
    }
    return (f_fill_fractional(f));
}

char        *ftoa(long double num) //добавить точность для обрезки
{
    varfloat f;

    f.sym = 0;
    if (num < 0)
        f.sym = 1;
    f.integer = (long long)num;
    f.tmp = num - f.integer;
    f.fractional = f.tmp;
    f.lenbef = ft_inter_len(num);
    f.lenaf = f.lenbef + 1;
    f.cp_lenbef = f.lenbef;
    f.cp_lenaf = f.lenaf;
    f.cp_fractional = f.fractional;
    f.cp_integer = f.integer;
    if (!(f.string = (char *)malloc(sizeof(char) * (f.lenbef + 2 + 40))))
        return (NULL);
    if (f.integer < 0 || f.fractional < 0)
        return (f_fill_integer_min(&f));
    else
        return (f_fill_integer(&f));
    return (NULL);
}
