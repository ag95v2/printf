/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:55:09 by dpenney           #+#    #+#             */
/*   Updated: 2019/11/29 14:55:10 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "read_spec.h"
#include "apply_spec.h"

/*
**	Print all normal chars until % or '\0'
**	Return:
**	-pointer to first '%' if string contains '%'
**	-0 otherwise
*/

const char	*print_until_percent(const char *format)
{
	while (*format && *format != '%')
		ft_putchar(*(format++));
	return (*format ? ++format : 0);
}

/*
**	Determine type of next arg according to spec
**	Extract argument from original vl
**	Return its string representation
*/

char		*get_arg_str(t_spec *spec, va_list *vl)
{
	void		*arg;
	char		*res;
	t_conv_f	*action;
	int			error;

	error = 0;
	if (!(action = find_action(*spec)) ||
		!(arg = action->arg_extract(*spec, vl)) ||
		!(res = action->to_str(arg)))
		error = 1;
	if (action->cleanup_needed)
		free(arg);
	return (error || !(res = apply_spec(res, spec)) ? 0 : res);
}

void		handle_stupid_c0_special_case(char *s, t_spec spec)
{
	int	len;

	len = ft_strlen(s);
	s[len - 1] = 0;
	if (!spec.flag_dash)
	{
		ft_putstr(s);
		ft_putchar('\0');
	}
	else
	{
		ft_putchar('\0');
		ft_putstr(s);
	}
}

/*
** Stupid special case with %c and 0 char (which HAS to be printed)
*/

int			ft_printf(const char *format, ...)
{
	va_list vl;
	t_spec	spec;
	char	*s;

	va_start(vl, format);
	while ((format = print_until_percent(format)))
	{
		format = read_spec(format, &spec);
		if (!format || !(s = get_arg_str(&spec, &vl)))
			return (-1);
		if (spec.stupid_c0_special_case)
			handle_stupid_c0_special_case(s, spec);
		else
			ft_putstr(s);
		if (spec.conv != 's')
			free(s);
	}
	va_end(vl);
	return (0);
}
