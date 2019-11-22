#include "ft_printf.h"

/*
Почему точность -1?
*/

void        init_spec(t_spec *spec)
{
    spec->flag_zero = 0;
    spec->flag_hash = 0;
    spec->flag_plus = 0;
    spec->flag_dash = 0;
    spec->flage_space = 0;
    spec->width = 0;
    spec->precision = -1;
    spec->length = 0;
    spec->conv = 0;
    spec->stupid_c0_special_case = 0;
}

/*
Фиксируем присутствие флагов; 
*/

void        read_flag(const char c, t_spec *spec)
{
    if (c == '+')
        spec->flag_plus = 1;
    if (c == '-')
        spec->flag_dash = 1;
    if (c == ' ')
        spec->flag_space = 1;
    if (c == '#')
        spec->flag_hash = 1;
    if (c == '0')
        spec->flag_zero = 1;
}

/*
Приходит текст, который читается в цикле и если найдены
символы в виде флагов printf, то отправляется для отметки
в структуре флагов void read_flaG(...);
*/

const char *read_flags(const char *f, t_spec *spec)
{
    while (*f == '+' || *f == ' ' || *f == '#' || *f == '0')
        read_flag(*(f++), spec);
    return (f);
}

/*
Приходит текст и хранилище символов;
Читается ширина после флагов и здесь сразу определяется
цифра ли это? 
Если это цифра, то вводится в ширину. 

?? А что, если ширина больше 9? Ведь запоминается только
простое число.

Дальше пока идёт число - пропускается. Почему?
*/

const char  *read_width(const char *f, t_spec *spec)
{
    if (ft_isdigit(*f))
        spec->width = ft_atoi(f);
    while (ft_isdigit(*f))
        f++;
    return (f);
}

/*
Вывод максимальных длин в зависимости от спецификатора.
В цикле проходим на соответствие.
Внутри цикла вводим условия Если, чтобы обозначить
присутствие.
Oдна l - для long int и unsigned long int;
ll - long long int and unsigned long long int;
h - short int and unsigned short int;
hh - char and unsigned char;
L - long double;
*/

const char  *read_length(const char *f, t_spec *spec)
{
    while (*f == 'l' || *f == 'L' || *f == 'h')
    {
        if (*f == 'l' && *(f + 1) == 'l' && spec->length < ll)
            spec->length = ll;
        if (*f == 'l' && *(f + 1) != 'l' && spec->length < l)
            spec->length = l;
        if (*f == 'h' && *(f + 1) == 'h' && spec->length < hh)
            spec->length = hh;
        if (*f == 'h' && *(f + 1) != 'h' && spec->length < h)
            spec->length = h;
        if (*f == 'L' && spec->length < L)
            spec->length = L;
        f++;
    }
    return (f);
}

/*
Если нет спецификаторов, то выводи ошибку.
Почему? Ведь могут быть просто предложения.
*/
const char  *read_conv_spec(const char *f, t_spec *spec)
{
    if (*f != 'd' && *f != 'i' && *f != 'o' && *f != 'u' \
            *f != 'x' && *f != 'X' && *f != 'f' && *f != 'c' \
            && *f != 's' && *f != 'p' && *f != '%')
            return (0);
    spec->conf = *f;
    return (++f);
}

/*
Инициализируются переменные, чтобы запомнить какие флаги
есть;
format = read_flags(format, spec) - чтобы найти спец символы
и обозначить единицей, если они присутствуют. А когда закон-
ится поиск флагов, то возвращается указатель, передвинутый
на опр-ое кол-во символов после флагов;
Так же ищется и ширина;

?? После флагов и ширины если есть точка, то заходим и обозна-
чаем это нулем. Почему не 1, а 0?

Дальше передается на чтение цифры для постановки точности.
После этого определяем длину через символы l, L и h. 
*/

const char *read_spec(const char *format, t_spec *spec)
{
    init_spec(spec); //инициализация списка
    format = read_flags(format, spec);
    format = read_width(format, spec);
    if (*format == '.')
    {
        spec->precision = 0; //Почему здесь обнуляем? Почему в структуре -1?
        format = read_precision(++format, spec);
    }
    format = read_length(format, spec);
    format = read_conv_spec(format, spec);
    return (format);   
}