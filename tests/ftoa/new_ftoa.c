#include <stdio.h>
#include <stdlib.h>

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

typedef struct variablesforfloat
{
    char        *string;
    long long   integer;
    long double fractional;
    int         sym;
    long long   tmp;
    int         lenbef;
    int         lenaf;
    int         i;
    int         tmp2;
}               varfloat;

/*
**  at f_p_zero is working if precision
**  is zero.
**  we are rounding up if in fractional part
**  some numbers more or equal to 0.95;
*/

char        *f_p_zero(varfloat *f)
{
    if (f->fractional >= 0.95)
        f->integer += 1;
    f->string[f->lenbef--] = '\0';
    if (f->sym)
    {
        f->string[0] = '-';
        f->i++;
        f->integer *= -1;
    }
    while (f->i <= f->lenbef)
    {
        f->string[f->lenbef--] = f->integer % 10 + '0';
        f->integer /= 10;
    }
    return (f->string);
}

/*
** Возьмём для примера число 123.39 с точностью 1 после 
** точки. Смотрим остаток - там больше 0.5 осталось?
** если да, то округляем близлежащее справа число 
** Но так как сотая часть равна 9, то обнуляем сотую часть
** и добавляем единичку справа 
*/
char        *f_rounding_up(varfloat *f)
{
    if (f->fractional >= 0.5 && f->string[f->lenaf - 1] != 9)
          f->string[f->lenaf - 1] += 1;
  if (f->fractional >= 0.5 && f->string[f->lenaf - 1] == 9)
    {
        while (f->string[f->lenaf - 1] == '9')
        {
            f->string[f->lenaf - 1] = '0';
            f->string[f->lenaf - 3] += 1;
        }
    }
    f->string[f->lenaf] = '\0';
    return (f->string);
}

/* 
** We are filling fractional numbers through
** number multiplication to 10 and taking integer
** number; After it - recording this number to string
** and deleting this integer number.
*/ 

char        *f_fill_fractional(varfloat *f, int p)
{
    f->i = 0;
    while (f->i < p)
    {
        f->fractional *= 10;
        f->tmp2 = (int)f->fractional;
        f->string[f->lenaf++] = f->tmp2 + '0';
        f->fractional = f->fractional - f->tmp2;
        f->i++;
    }
    return (f_rounding_up(f));
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

// char        *f_fill_integer_min(varfloat *f, int p)
// {
//     f->fractional *= (-1);
//     f->integer *= (-1);
//     f->string[f->lenbef--] = '.';
//     f->string[0] = '-';
//     while (0 < f->lenbef)
//     {
//         f->string[f->lenbef--] = f->integer % 10 + '0';
//         f->integer /= 10;
//     }
//     return (f_fill_fractional(f, p));
// }

char        *f_fill_integer_min(varfloat *f, int p)
{
    f->fractional *= -1;
    f->string[f->lenbef--] = '.';
    f->string[0] = '-';
    if (f->integer == -0)
    {
        f->string[1] = '0';
        f->string[0] = '.';
        f->lenbef +=2;
    }
    f->integer *= -1;
    while (0 < f->lenbef)
    {
        f->string[f->lenbef--] = f->integer % 10 + '0';
        f->integer /= 10;
    }
    return (f_fill_fractional(f, p));
}

char        *ft_ftoa(long double num, int p)
{
    varfloat f;
    char    *string;

    f.sym = 0;
    f.i = 0;
    if (num < 0)
        f.sym = 1;
    f.integer = (long long)num;
    f.fractional = num - f.integer;
    f.lenbef = ft_inter_len(num);
    f.lenaf = f.lenbef + 1;
    if (!(f.string = (char *)malloc(sizeof(char) * (f.lenbef + p + 2))))
        return (NULL);
    if (p == 0)
        return (f_p_zero(&f));
    else if (f.integer < 0 || f.fractional < 0)
        return (f_fill_integer_min(&f, p));
    // else if (f.integer == 0)
    //     return (f_fill_integer_zero(&f, p));
    // else
    //     return (f_fill_integer(&f, p));
    return (NULL);
}

int main(void)
{
    float   a;
    char    *b;

    a = -51.96;
    printf("GENERAL %0.6f\n", a);
    b = ft_ftoa(a, 1);
    printf("MY      %s\n", b);
    return (0);
}