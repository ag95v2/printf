#include "printf.h"
#include "read_spec.h"
#include "apply_spec.h"

/*
Отправляется на печать всё, пока не встретит знак процента
А если нашёл либо строка закончилась, то отправляет строку
после знака процента обратно либо нуль
*/

const char  *print_until_percent(const char *format)
{
    while (*format && *format != '%')
        ft_putchar(*(format++));
    return (*format ? ++format : 0);
}

char            *get_arg_str(t_spec *spec, va_list *vl)
{
    void        *arg;
    char        *res;
    t_conv_f    *action;
    int         error;

    error = 0;
    if (!(action = find_action(*spec)) ||
        !(arg = action->arg_extract(*spec, vl)) ||
        !(res = action->to_str(arg)))
        error = 1;
    if (action->cleanup_needed)
        free(arg);
    return (error || !(res = apply_spec(res, spec)) ? 0 : res);
}

/*
** Создана структура va_list и в новую созданную
** переменную vl передаются аргументы, ожидаемые от поль-ля;
** в цикле читается всё, пока не дойдет до знака процента
** Почему цикл? Потому как пока возвращается что-то - значит
** в передаваемой строке ещё есть что-то.
** А если вернется 0, то строка закончится, цикл автоматически
** закроется.
** далее читаются символы в отдельной функци read_spec, куда
** передаются строка и инициализированный список с переменными
** Идёт чтение спецификатора. Если нет строки,  либо нет 
** спецификатора, то возвращается ошибкой. В get_arg_str читаем
** спецификаторы. 
*/

int     ft_printf(const char *format, ...)
{
    va_list vl;
    t_spec  spec;
    char    *s;

    va_start(vl, format);
    while ((format = print_until_percent(format)))
    {
        format = read_spec(format, &spec);
        if (!format || !(s = get_arg_str(&spec, &vl)))
            return (-1);
        if (spec.stupid_c0_special_case)
            handle_stupid_c0_special_case(s, spec);
        else
        {
            ft_putstr(s);
        }
        if (spec.conv != 's')
        {
            free(s);
        }
    }
    va_end(vl);
    return (0);
}