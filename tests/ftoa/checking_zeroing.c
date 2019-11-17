#include <stdio.h>
#include <stdlib.h>

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
    int         cp_lenbef;
    int         cp_lenaf;
    int         number;
    long long   cp_integer;
    long double cp_fractional;
}               varfloat;

int	ft_inter_len(long long inter, long double fractional)
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
** Возьмём для примера число 123.39 с точностью 1 после 
** точки. Смотрим остаток - там больше 0.5 осталось?
** если да, то округляем близлежащее справа число 
** Но так как сотая часть равна 9, то обнуляем сотую часть
** и добавляем единичку справа 
*/
char        *f_rounding_up(varfloat *f)
{
    if (f->fractional >= 0.5 && f->string [f->lenaf - 1] != '9')
          f->string[f->lenaf - 1] += 1;
    else if (f->fractional >= 0.5 && f->string[f->lenaf - 1] == '9')
        while (f->string[f->lenaf - 1] == '9')
        {
            if (f->string[f->lenaf - 2] == '.')
            {
                f->string[f->lenaf - 1] = '0';
                f->string[f->lenaf - 3] += 1;
            }
            else if (f->string[f->lenaf - 2] != '.')
            {
                f->string[f->lenaf - 1] = '0';
                f->string[f->lenaf - 2] += 1;
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

char        *f_fill_zero_fractional(varfloat *f, int p)
{
    if (f->fractional < 0)
    {
        f->string[f->lenbef] = '-';
        f->string[f->lenbef] = '0';
    }
    else
        f->string[f->lenbef - 1] = '0';
    return (f_fill_fractional(f, p));
}

/*
**  at f_p_zero is working if precision
**  is zero.
**  we are rounding up if in fractional part
**  some numbers more or equal to 0.95;
*/

char        *f_p_zero(varfloat *f)
{
    f->i = 0;
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

char        *f_fill_integer_min(varfloat *f, int p)
{
    f->fractional *= -1;
    f->string[f->lenbef--] = '.';
    f->string[0] = '-';
    f->integer *= -1;
    while (0 < f->lenbef)
    {
        f->string[f->lenbef--] = f->integer % 10 + '0';
        f->integer /= 10;
    }
    return (f_fill_fractional(f, p));
}

char        *f_fill_integer(varfloat *f, int p)
{
    f->string[f->lenbef--] = '.';
    while (0 <= f->lenbef)
    {
        f->string[f->lenbef--] = f->integer % 10 + '0';
        f->integer /= 10;
    }
    return (f_fill_fractional(f, p));
}

/*char        *f_checker_zeroing(char *str, varfloat *f, int p)
{
    f->number = 9;
    f->i = 0;
    if (((f->fractional * 10) == f->number) || f->integer == 0)
    {
        while (f->fractional * 10 >= 0.5)
        {
            f->fractional *= 10;
        }
        while (str[f->i] == 0)
        {
            
        }
    }
}*/

char        *ft_ftoa(long double num, int p)
{
    varfloat f;

    f.sym = 0;
    if (num < 0)
        f.sym = 1;
    f.integer = (long long)num;
    f.fractional = num - f.integer;
    f.lenbef = ft_inter_len(num, f.fractional);
    f.lenaf = f.lenbef + 1;
    f.cp_lenbef = f.lenbef;
    f.cp_lenaf = f.lenaf;
    f.cp_fractional = f.fractional;
    f.cp_integer = f.integer;
    if (!(f.string = (char *)malloc(sizeof(char) * (f.lenbef + p + 2))))
        return (NULL);
    if (p == 0)
        return (f_p_zero(&f));
    else if (f.integer < 0 || f.fractional < 0)
        return (f_fill_integer_min(&f, p));
    else
        return (f_fill_integer(&f, p));
    return (NULL);
}

int main(void)
{
    float   a;
    char    *b;

    /*Можно решить добавлением цикла при получении строки. В строке смотрим если все равняется
    многим нулям, а полученная цифра являлась чередой девяток (проверяем integer and fractional),
    то объединяем строку, содержащую единицу с количеством нулей, которые округлились от 99...999..
    ? Как понять, что во fractional и integer есть череда девяток

    Узнать сколько девяток в целочисленных через получение остатка
    от деления на 10 и сравнить с lenbef. Если они равны, то проверить fractional через 
    умножение на 10. Переходим к округлению. Добавляем условие - если округление идет в цифру,
    которая является девяткой и другие цифры девятки из целочисленных, то всё обнуляем, ставим 
    заново точку и добавляем спереди единицу через ft_strsub или что-то подобное для присоеди
    нения.
     */
    float c = 99999.99;
    printf("\033[0;32mTASK 2 - ZEROING:\nGENERAL %0.f\n", c);
    b = ft_ftoa(c, 0);
    printf("MY      %s\n", b);
    printf("GENERAL TESTING\n");
    printf("LIBS: %f\n", 1444565444646.6465424242242);
    printf("LIBS: %s\n", ft_ftoa(1444565444646.6465424242242, 6));
    return (0);
}