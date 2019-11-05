
#include "printf.h"

/*
**	Return appropritate action according to spec if such exists else 0
*/

t_conv_f	*find_action(t_spec spec)
{
	static t_conv_f	actions[] = ACTIONS;
	static t_conv_f	action;
	int				i;

	i = 0;
	while ((action = actions[i++]).specifiers)
		if (ft_strchr(action.specifiers, spec.conv))
			return (&action);
	return (0);
}
