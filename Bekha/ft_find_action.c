#include "ft_printf.h"

/*
Записываются переменные 
В цикле из массива что-то впихивается в 
action из содержания actionS, который наполнен 
typedef struct s_conv_f
{
    char    *specifiers;
    char    *(*to_str)(void *arg);
    void    *(*arg_extract_)(t_spec spec, va_list *vl);
    int     cleanup_needed;
};          t_conv_f;

? Вообще как  работает это?

# define ACTIONS {\
    {"di", &w_itoa_b10, &int_extractor, 1},\
    {"u", &w_itoa_b10u, &int_extractor, 1},\
    {"o", &w_itoa_b8, &int_extractor, 1},\
    {"xp", &w_itoa_x, &int_extractor, 1},\
    {"X", &w_itoa_X, &int_extractor, 1},\
    {"f", &w_ftoa, &float_extractor, 1},\
    {"c", &w_ctoa, &char_extractor, 1},\
    {"s", &w_stoa, &str_extractor, 0},\
    {"%", &w_percent, &dummy_extractor, 0},\
    {0, 0, 0, 0}\
}
В этой функции всё закидывается в массив actionS;
Массив состоит из
1.символа спецификатора;
2.адреса функции
3.обёртки, адреса функции, который выводит аргумент и
4.?? для нужен нуль?
Далее записывается эта инормация в переменную action,
пока не дойдёт до нуля конце массива, что означает
конец ифнормации. В строке с условным оператором проверяется
какой спецификатор нам прислан. 
Далее возвращается обратно адрес
на переменную с массивом
*/

t_conv_f    *find_action(t_spec spec)
{
    static  t_conv_f actionS [] = ACTIONS;
    static  t_conv_f action;
    int              i;

    i = 0;
    while (action = actionS[i++]).specifiers)
        if (ft_strchr(action.specifiers, spec.conv)) //проверка спецификаторов
            return (&action);
    return (0);
}