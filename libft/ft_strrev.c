
#include "libft.h"

void			ft_strrev(char *s)
{
	int		len;
	int		i;
	char	tmp;

	i = 0;
	len = ft_strlen(s);
	while (i < (len - i - 1))
	{
		tmp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = tmp;
		i++;
	}
}


