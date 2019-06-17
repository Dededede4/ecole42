/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 14:26:16 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:45:20 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void		set_precision(t_format *env, t_arg *arg, va_list ap)
{
	if (env->format[env->position] == '.')
	{
		env->position++;
		arg->precision_is_set = 1;
		if (env->format[env->position] == '*')
		{
			arg->precision = va_arg(ap, int);
			if (arg->precision < 0)
				arg->precision_is_set = 0;
		}
		else
		{
			arg->precision = 0;
			while (ft_isdigit(env->format[env->position]))
			{
				arg->precision *= 10;
				arg->precision += (int)(env->format[env->position]) - 48;
				env->position++;
			}
		}
	}
	else
		env->position++;
}

int				parse_arg_precision(t_format *env, t_arg *arg,
										int tmp, va_list ap)
{
	int			test;

	tmp = env->position;
	arg->precision_is_set = 0;
	while ((test = ft_is_end_of_arg(env, env->position)) > 0)
		set_precision(env, arg, ap);
	if (test == -1)
		return (0);
	env->position = tmp;
	return (1);
}
