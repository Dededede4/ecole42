/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 14:43:44 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:45:28 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int		inner_set_type(char type, t_arg *arg)
{
	if (type == 'b')
		arg->type = U_BIN;
	if (arg->type == T_DEFAULT)
		return (-1);
	return (1);
}

static int		set_type(char type, t_arg *arg)
{
	if (type == 'd' || type == 'i' || type == 'D')
		arg->type = S_DEC;
	else if (type == 'u' || type == 'U')
		arg->type = U_DEC;
	else if (type == 'x')
		arg->type = L_HEXA;
	else if (type == 'X')
		arg->type = U_HEXA;
	else if (type == 'o' || type == 'O')
		arg->type = OCTAL;
	else if (type == 'c' || type == 'C')
		arg->type = U_CHAR;
	else if (type == 's' || type == 'S')
		arg->type = STRING;
	else if (type == 'p')
		arg->type = PTR;
	else if (type == '%')
		arg->type = PERCENT;
	if (type == 'S' || type == 'C' || type == 'D'
					|| type == 'U' || type == 'O')
		arg->modifier = L;
	if (arg->type == T_DEFAULT)
		return (inner_set_type(type, arg));
	return (1);
}

int				parse_arg_type(t_format *env, t_arg *arg)
{
	int			test;

	arg->type = T_DEFAULT;
	while ((test = ft_is_end_of_arg(env, env->position)) > 0)
		env->position++;
	if (test < 0)
		return (0);
	if (set_type(env->format[env->position], arg) < 0)
		return (0);
	env->position++;
	return (1);
}
