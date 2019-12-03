
#include <stdio.h>
#include "ftoa.h"

int	main()
{
	long double	x;

	x = 121.05l;
	printf("%s\n",ftoa(x));
	return (0);
}
