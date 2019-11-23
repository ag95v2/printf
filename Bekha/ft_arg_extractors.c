#include "printf.h"
#include "fp_type.h"

/*
Если без символа
*/

void    extr_sint(t_spec spec, va_list *vl, long long *p)
{
    if (spec.length == ll)
        p = va_arg(*vl, long long);
    else if (spec.length == l)
        p = va_arg(*vl, long);
    else
        p = va_arg(*vl, int);
    return ((void)p);
}

/*
Если переменная символьная, то сюда;
А также учитываются флаги, в зависимости от которых
берется определнный тип переменных;.
*/

void    extr_uint(t_spec spec, va_list *vl, long long *p)
{
    if (spec.length == ll)
        p = va_arg(*vl, unsigned long long);
    else if (spec.length == l)
        p = va_arg(*vl, unsigned long);
    else
        p = va_arg(*vl, unsigned int);
    return ((void *)p);
}

/*
is_usgn определяет в какой конвертации число пришло.
Если это одна из них, то меняется формат обычного в 
особенные:
1. без знака;
2. в двоичной системе;
3. в шестнадцатеричной;
*/

int     is_usgn(t_spec spec)
{
    if (spec.conv == 'u' || \
        spec.conv == 'o' || \
        spec.conv == 'x' || \
        spec.conv == 'X')
            return (1);
    return (0);
}

/*
В зависимости от того какого формата пришла переменная
выбирается вывод переменной - unsigned или signed;
*/

i_extr_fun  choose_i_extr(t_spec spec)
{
    return (is_usgn(spec) ? &extr_uint : &extr_sint)
}

/*
Как отправляется аргумент в функции chooise_i_extr?
*/

void    int_extractor(t_spec spec, va_list *vl)
{
    long long   *p;
    if (!(choose_i_extr(spec)(spec, vl, &p)))
        return ((void)&p);
}

void    float_extractor(t_spec spec, va_list *vl)
{
    long double     *p;

    if (spec.length == ll || \
        spec.length == l || \
        spec.length == L)
            *p = va_arg(*vl, long double);
    else
            *p = va_arg(*vl, double);
    return ((void)&p);
}

/*
для чего приводится к void?
Чтобы вернуть void;
Выводится один символ char;
*/

void    char_extractor(t_spec spec, va_list *vl)
{
    char    p[2];

    (void)spec;
    p[0] = va_arg(*vl, int);
    p[1] = '\0';
    return ((void)&p);
}

/*
Через va_arg забираем аргумент в формате char *
т.е. строки;
Если нет аргумента и указана положительная точность
до 6, то возврашать пустую строку.
Если строки нет, то возвращается нуль.
*/

void    *str_extractor(t_spec spec, va_list *vl)
{
    char    *arg;

    arg = va_arg(*vl, char *);
    if (!arg && spec.precision > 0 && spec.precision < 6)
        arg = "";
    if (!arg)
        arg = "(null)";
    return ((void *)arg);
}

void    binary_extractor(t_spec spec, va_list *vl)
{
    char    arg[66];

    arg = va_arg(*vl, char *);
    return ((void)&arg);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void *dummy_extractor(t_spec, va_list *vl)
{
    return ((void*)1);
}
#pragma GCC diagnostic pop