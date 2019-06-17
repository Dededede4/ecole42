/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 13:05:21 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:44:42 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void		init_flags(t_flags *flags)
{
	flags->alternate_form = 0;
	flags->force_sign = 0;
	flags->add_space = 0;
	flags->zero_pad = 0;
	flags->rev_pad = 0;
}

int				parse_arg_flags(t_format *env, t_arg *arg, int tmp)
{
	int			test;
	t_flags		flags;

	init_flags(&flags);
	tmp = env->position;
	while ((test = ft_is_end_of_arg(env, env->position)) > 0)
	{
		if (env->format[env->position] == '#')
			flags.alternate_form = 1;
		if (env->format[env->position] == '-')
			flags.rev_pad = 1;
		if (env->format[env->position] == '+')
			flags.force_sign = 1;
		if (env->format[env->position] == '0' &&
			!ft_isdigit_nozero(env->format[env->position - 1]))
			flags.zero_pad = 1;
		if (env->format[env->position] == ' ')
			flags.add_space = 1;
		env->position++;
	}
	arg->flags = flags;
	if (test == -1)
		return (0);
	env->position = tmp;
	return (1);
}
