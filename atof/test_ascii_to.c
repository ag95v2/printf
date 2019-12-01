
#include <stdio.h>
#include "ft_fp.h"

int main(int argc, char **argv)
{
	t_decimal	repr;
	char		s[80];

	positive_ascii_to(&repr, argv[1]);
	to_ascii(repr, s);
	printf("%s\n", s);
	return (0);
}
