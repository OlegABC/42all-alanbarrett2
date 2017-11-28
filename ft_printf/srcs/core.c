/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 18:17:42 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/core.h"

/*
 ** List of all types and callbacks
*/

t_types	g_types[ARGS_COUNT] = {
	{'c', type_c}, {'C', type_c_upper}, {'s', type_s}, {'S', type_s},
	{'d', type_d}, {'i', type_d}, {'%', type_percentage}, {'p', type_p},
	{'o', type_o}, {'x', type_x}, {'X', type_x_upper}, {'u', type_u},
	{'D', type_d_upper}, {'O', type_o_upper}, {'U', type_u_upper},
	{'a', type_a}, {'A', type_a_upper}
};

/*
 ** Call the type with the current char, using the g_types array
 ** Display some padding if the char isn't a valid type
*/

int	ft_call_type(char **str, va_list args, t_flags flags)
{
	int arg;
	int size;

	arg = 0;
	while (arg < ARGS_COUNT)
	{
		if (**str == g_types[arg].name)
		{
			*str += 1;
			flags.type = g_types[arg].name;
			return (g_types[arg].f(args, flags));
		}
		arg++;
	}
	size = 1;
	if (!flags.minus)
		size = ft_pad(flags, size);
	write(STDOUT, *str, 1);
	if (flags.minus)
		size = ft_pad(flags, size);
	*str += 1;
	return (size);
}

/*
 ** Apply all length / flags / width / precision. Then, try to call a type.
 ** Stop the process if the n+1 char is EndOf str or if we found a stranger char
*/

int	ft_handle(char **str, va_list args)
{
	t_flags		flags;
	int			flags_found;

	ft_init_flags(&flags);
	while (**str)
	{
		flags_found = 0;
		while (ft_handle_length(str, &flags) ||
				ft_handle_flags(str, &flags) ||
				ft_handle_width(str, &flags, args) ||
				ft_handle_precision(str, &flags, args))
			flags_found = 1;
		if (ft_isalpha(**str) || **str == '%')
			return (ft_call_type(str, args, flags));
		else if (!*(*str + 1) || !flags_found)
			return (0);
	}
	return (0);
}

/*
 ** First function :
 ** start stdarg and process format with ft_handle if it's a % or display char
*/

int	ft_printf(const char *restrict format, ...)
{
	char	*str;
	int		bytes;
	va_list args;
	size_t	next;
	int 	tmp;

	bytes = 0;
	va_start(args, format);
	str = (char*)format;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if ((tmp = ft_handle(&str, args)) == -1)
				return (-1);
			bytes += tmp;
		}
		else
		{
			write(STDOUT, str, (next = (ft_strchr(str, '%')) ?
								ft_strchr(str, '%') - str : ft_strlen(str)));
			bytes += next;
			str += next;
		}
	}
	va_end(args);
	return (bytes);
}
