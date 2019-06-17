/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_min.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 23:19:24 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:44:58 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void		parse_digit(t_format *env)
{
	env->position++;
	while (ft_isdigit(env->format[env->position]))
		env->position++;
}

static void		inner_set_min(t_format *env, t_arg *arg)
{
	arg->min *= 10;
	arg->min += (int)(env->format[env->position]) - 48;
	env->position++;
}

static void		set_min(t_format *env, t_arg *arg, va_list ap)
{
	if (env->format[env->position] == '.')
		parse_digit(env);
	else if (ft_isdigit(env->format[env->position]) &&
				env->format[env->position] != '0')
	{
		arg->min = (int)(env->format[env->position++]) - 48;
		while (ft_isdigit(env->format[env->position]))
			inner_set_min(env, arg);
	}
	else if (env->format[env->position] == '*' &&
				env->format[env->position - 1] != '.')
	{
		arg->min = va_arg(ap, int);
		if (arg->min < 0)
		{
			arg->min *= -1;
			arg->flags.rev_pad = 1;
		}
		env->position++;
	}
	else
		env->position++;
}

int				parse_arg_min(t_format *env, t_arg *arg, int tmp, va_list ap)
{
	int			test;

	tmp = env->position;
	while ((test = ft_is_end_of_arg(env, env->position)) > 0)
		set_min(env, arg, ap);
	if (test == -1)
		return (0);
	env->position = tmp;
	return (1);
}
