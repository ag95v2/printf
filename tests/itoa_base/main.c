
#include <stdio.h>
#include "libft.h"

void	test_decimal(long long n)
{
	printf("\n%lld\n", n);
	printf("%s\n", ft_itoa_base(n, "0123456789", 1));
}

void	test_HEX(long long n)
{
	printf("\n%llX\n", n);
	printf("%s\n", ft_itoa_base(n, "0123456789ABCDEF", 0));
}

void	test(long long n)
{
	test_decimal(n);
	test_HEX(n);
}

int main()
{
	long long	values[] = {1, -1, 0, 100, -100, 999999, -99999, 1234, -1234};
	int			i = 0;
	while (i < 9)
		test(values[i++]);
	return (0);
}
