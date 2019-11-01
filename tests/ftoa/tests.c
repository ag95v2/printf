
#include "prototypes.h"

void	test(float x)
{
	char	*res;

	printf("\n%-10s%f\n","libc:", x);
	res = flot(x);
	printf("%-10s%s\n","SO:", res);
	free(res);
	res = ft_ftoa(x);
	printf("%-10s%s\n","Behrooz:", res);
	free(res);
}

int main()
{
	test(1.23);
	test(0.123456789);
	test(123456789123456789);
	test(123.456);
	test(123456.78901234);
	test(11111111111.2222222222222);
	test(1111111111111.00000000000001);
	test(0.00000000000001);

	return 0;
}
