
/*
**	Here you can find declarations of integer conversion functions
*/

#include "printf.h"

char	*itoa_b10u(long long n)
{
	if (n < 0)
		n = n * (-1);
	return (ft_itoa_base(long long n, 10));
}

char	*itoa_b10(long long n)
{
	// Your code here
	// Convert long long to string base 10
	return (ft_itoa_base(long long n, 10));
}

char	*itoa_b2(long long n)
{
	// Your code here
	// Convert long long to string base 2
	return (ft_itoa_base(long long n, 2));
}

char	*itoa_b8(long long n)
{
	// Your code here
	// Convert long long to string base 8
	return (ft_itoa_base(long long n, 8));
}

char	*itoa_bX(long long n)
{
	// Your code here
	// Convert long long to string base hex in uppercase
	return ("1AB2");
}

char	*itoa_bx(long long n)
{
	// Your code here
	// Convert long long to string base hex in lowecase
	return ("1ab2");
}
