#ifndef T_FLOAT_H
#define T_FLOAT_H

typedef struct	s_float
{
	unsigned long int	mant;
	unsigned short		exp;
	char				sign;
	unsigned long int	mant_mask;
	int					mask_shift;
	
}				t_float;

#endif
