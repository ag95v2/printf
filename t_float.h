#ifndef T_FLOAT_H
#define T_FLOAT_H

#define CRUTCH_FLOAT_PRECISION_CONSTANT 30

typedef struct	s_float
{
	unsigned long int	mant;
	unsigned short		exp;
	unsigned short		sign;
	unsigned long int	mant_mask;
	int					mask_shift;
	int					precision;
}				t_float;

#endif
