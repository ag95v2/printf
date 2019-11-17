
#ifndef PRINTF_H
#define PRINTF_H

#include "libft.h"
#include <stdarg.h>

enum length		{none, hh, h, l, ll, L}; 

/*
**	Structure that stores our internal representation of "user request"
*/

typedef struct		s_spec
{
	int				flag_zero;
	int				flag_hash;
	int				flag_plus;
	int				flag_dash;
	int				flag_space;

	int				width;
	int				precision;
	enum length		length;

	char			conv;
	int				stupid_c0_special_case;
}					t_spec;

/*
**	Generalized conversion function
**	Generalized argument extractor function
**  And all of its specifiers
*/

typedef struct		s_conv_f
{
	char			*specifiers;
	char			*(*to_str)(void *arg);
	void			*(*arg_extract)(t_spec spec, va_list *vl);
	int				cleanup_needed;
}					t_conv_f;

/*
**	Integer convertors
**  TODO: replace stubs with normal functions
*/

char	*itoa_b10u(long long n);
char	*itoa_b10(long long n);
char	*itoa_b2(long long n);
char	*itoa_b8(long long n);
char	*itoa_bX(long long n);
char	*itoa_bx(long long n);

/*
**	Integer convertors wrappers
*/

char	*w_itoa_b10u(void *n);
char	*w_itoa_b10(void *n);
char	*w_itoa_b2(void *n);
char	*w_itoa_b8(void *n);
char	*w_itoa_X(void *n);
char	*w_itoa_x(void *n);

/*
**	Non-integer convertors
**  TODO: replace stubs with normal functions
*/

char	*ftoa(long double x);
char	*ctoa(char c);
char	*stoa(char *s);
char	*ptoa(void *p);
char	*percent_to_a();

/*
**	Non-integer convertors wrappers
*/

char	*w_ftoa(void *x);
char	*w_ctoa(void *x);
char	*w_stoa(void *x);
char	*w_ptoa(void *x);
char	*w_percent(void *x);

/*
**	Argument extractors
*/

void	*int_extractor(t_spec spec, va_list *vl);
void	*float_extractor(t_spec spec, va_list *vl);
void	*char_extractor(t_spec spec, va_list *vl);
void	*str_extractor(t_spec spec, va_list *vl);
void	*dummy_extractor(t_spec spec, va_list *vl);


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

struct	varftoa
{
	long double		fraction;
	long long		inter;
	long double		tmp;
	char			*str;
	int				len_till_dot;
	int				i;
	int				len_af_dot;
};

t_conv_f	*find_action(t_spec spec);

int			ft_printf(const char *format, ...);
#endif
