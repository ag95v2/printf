
#ifndef PRINTF_H
#define PRINTF_H

#include "libft.h"
#include <stdarg.h>

enum length		{hh, h, l, ll, L}; //int-ая переменная, кот-ая принимает максимум 5 значений. И каждому из
									//значений присвоили название. 

//enum conv_spec	{d, i, o, u, x, X, f}

typedef struct		s_spec
{
	int				flag_zero;
	int				flag_hash;
	int				flag_plus;
	int				flag_dash;
	int				flag_space;

	int				width;
	int				precision;
	enum length		len;

	char			conv;
}					t_spec

#endif
