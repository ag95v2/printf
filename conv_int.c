
/*
**	Here you can find declarations of integer conversion functions
*/

#include "printf.h"
#include "libft.h"

#define	BINARY	"01"
#define OCTAL	"01234567"
#define DECIMAL "0123456789"
#define HEX_L	"0123456789abcdef"
#define HEX_U	"0123456789ABCDEF"

char	*itoa_b10u(long long n)
{
	return (ft_itoa_base(n, DECIMAL, 0));
}

char	*itoa_b10(long long n)
{
	return (ft_itoa_base(n, DECIMAL, 1));
}

char	*itoa_b2(long long n)
{
	return (ft_itoa_base(n, BINARY, 0));
}

char	*itoa_b8(long long n)
{
	return (ft_itoa_base(n, OCTAL, 0));
}

char	*itoa_bX(long long n)
{
	return (ft_itoa_base(n, HEX_U, 0));
}

char	*itoa_bx(long long n)
{
	return (ft_itoa_base(n, HEX_L, 0));
}
