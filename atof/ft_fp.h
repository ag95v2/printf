#ifndef FT_FP_H
#define FT_FP_H

#define LD_MAX_DIGITS 20000

/*
**	Example:
**  buff		start	end
**	 |			|		 |
**	 V			V		 V
**   ..garbage..1234512345
**	after_dot = 5
**	is_negative = 1
**	encodes:  -12345.12345
**
**	end points to last digit
**	Store digits, not ascii codes
*/

typedef struct	s_decimal
{
	char		buff[LD_MAX_DIGITS];
	char		*end;
	char		*start;
	int			after_dot;
	int			is_negative;
}				t_decimal;


int		to_ascii(t_decimal repr, char *s);
void	positive_ascii_to(t_decimal *repr, char *s);
void	add_positive_decimal(t_decimal *a, t_decimal *b);
void	multiply_positive_decimal(t_decimal *a, t_decimal *b);
void	power_positive_decimal(t_decimal *x, int pow);

#endif
