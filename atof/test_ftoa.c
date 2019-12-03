
#include <stdio.h>
#include "ftoa.h"

int	main()
{
	long double	x;

	x = 1.0l;
	printf("%s\n",ftoa(x));
	return (0);
}
