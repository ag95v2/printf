#include <stdio.h>
#include <stdlib.h>

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
** We are filling fractional numbers through
** number multiplication to 10 and taking integer
** number; After it - recording this number to string
** and deleting this integer number.
*/

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*str;

	if (!s)
		return (NULL);
	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (len > i)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char        *ft_rounding_up(varfloat *f, int p)
{
    if (f->cp_fractional < 0)
        f->cp_fractional *= -1;
    if (f->cp_fractional >= 0.5 && f->res[f->p - 1] != '9')
        f->res[f->p - 1] += 1;
    else if (f->cp_fractional >= 0.5 && f->res[f->p - 1] == '9')
        while (f->res[f->p - 1] == '9')
        {
            if (f->res[f->p - 2] == '.')
            {
                f->res[f->p - 1] = '0';
                f->res[f->p - 3] += 1; 
            }
            else if (f->res[f->p - 1] != '.')
            {
                f->res[f->p - 1] = '0';
                f->res[f->p - 2] += 1;
            }
        }
    f->res[f->p] = '\0';
    return (f->res);
}

/*
** Cuting our string depending on length of precision;
** And sending to function for rounding up;
*/

char        *ft_cut(varfloat *f, int p)
{
    if (p == 0)
    {
        f->p = p + f->cp_lenbef;
        f->res = ft_strsub(f->string, 0, f->p);
    }
    else
    {
        f->p = p + f->cp_lenbef + 1;
        f->res = ft_strsub(f->string, 0, f->p);        
    }
    while (p--)
    {
        f->cp_fractional *= 10;
        f->tmp2 = (int)f->cp_fractional;
        f->cp_fractional = f->cp_fractional - f->tmp2;
    }
    return (ft_rounding_up(f, p));
}

/*
** Than to fill string with fractional numbers;
*/

char        *f_fill_fractional(varfloat *f, int p)
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
    return (ft_cut(f, p));
}

/*
** for integer = 0 and some numbers in fracitonal
*/

char        *f_fill_zero_fractional(varfloat *f, int p)
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
    return (f_fill_fractional(f, p));
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
    if (f->integer == 0 && f->fractional < 0)
        return (f_fill_zero_fractional(f, p));
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

char        *ft_ftoa(long double num, int p) //добавить точность для обрезки
{
    varfloat f;

    f.sym = 0;
    if (num < 0)
        f.sym = 1;
    f.integer = (long long)num;
    f.tmp = num - f.integer;
    f.fractional = f.tmp;
    f.lenbef = ft_inter_len(num, f.fractional);
    f.lenaf = f.lenbef + 1;
    f.cp_lenbef = f.lenbef;
    f.cp_lenaf = f.lenaf;
    f.cp_fractional = f.fractional;
    f.cp_integer = f.integer;
    if (!(f.string = (char *)malloc(sizeof(char) * (f.lenbef + 2 + 40))))
        return (NULL);
 //   if (p == 0)
  //      return (f_p_zero(&f));
    if (f.integer < 0 || f.fractional < 0)
        return (f_fill_integer_min(&f, p));
    else
        return (f_fill_integer(&f, p));
    return (NULL);
}

int main(void)
{
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
    
    Лучше всю точность вывести, а потом сокращать. Когда видим, что пользователь хочет сокра
    щения до 2 (точность имеется ввиду), то проверяем на девятки целочисленные, проверяем первую
    цифру после точки на девятку, остальные на кол-во больше 0,5. Если всё так, то всё обнуляем и
    ставим единичку спереди, а через цикл нули до определенной точности. 

    Внимание! Нужно обработать только 9, 99, 999, остальные сами делаются. 
    Сначала обрезаем до необходимой точности через создание новой строки. А далее проверяем ячейку
    после вырезки +1. Если она равна либо больше 5 и все девятки в целых и после точки после обрезки
    то всё обнуляем и добавляем разряд. 

    Вопросы: 
    1. Почему появляется погрешность?
    2. Почему округление с новым разрядом происходит от числе 9999.999...., а от 9, 99, 999 нет?
    3. Какая максимальная точность, которая принимается в printf?
    
     */
     float a = -5.99;
     printf("\033[0;32mTASK 2 - ZEROING:\nGENERAL %0.1f\n", a);
     b = ft_ftoa(a, 1);
     printf("MY      %s\n", b);
    printf("GENERAL TESTING\n");
    long double c = 999999.99;
    printf("LIBS: %.1Lf\n", c);
    printf("MY:   %s\n", ft_ftoa(c, 1));
    printf("LIBS: {%.10lf}", -1444565444646.6465424242242454654);
    printf("\nMY: %s\n", ft_ftoa(-1444565444646.6465424242242454654, 10));
    return (0);
}