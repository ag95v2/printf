
#include <stdio.h>
#include "ftoa.h"

#include <float.h>

int	main()
{
	long double	x;

	x = -1l;
	x = DBL_MIN;
	printf("%s\n",ftoa(x));
	return (0);
}
