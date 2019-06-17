/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_modifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 12:18:46 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:45:10 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void		set_modifier(t_format *env, t_arg *arg,
								const char *form, int pos)
{
	if ((form[pos] == 'h') && arg->modifier == M_DEFAULT)
	{
		if (form[pos + 1] == 'h')
		{
			env->position++;
			arg->modifier = HH;
		}
		else
			arg->modifier = H;
	}
	else if (form[pos] == 'l')
	{
		if (form[pos + 1] == 'l')
		{
			arg->modifier = LL;
			env->position++;
		}
		else
			arg->modifier = L;
	}
	else if (form[pos] == 'j')
		arg->modifier = J;
	else if (form[pos] == 'z')
		arg->modifier = Z;
}

int				parse_arg_modifier(t_format *env, t_arg *arg)
{
	int			tmp;
	int			test;

	tmp = env->position;
	arg->modifier = M_DEFAULT;
	while ((test = ft_is_end_of_arg(env, env->position)) > 0)
	{
		set_modifier(env, arg, env->format, env->position);
		env->position++;
	}
	if (test == -1)
		return (0);
	env->position = tmp;
	return (1);
}
