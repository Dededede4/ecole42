/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 16:07:12 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:44:33 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int				ft_is_end_of_arg(t_format *env, int i)
{
	if (env->format[i] == '\0')
		return (-1);
	if (env->format[i] == 'h' || env->format[i] == 'j' ||
		env->format[i] == 'l' || env->format[i] == 'z' ||
		ft_isdigit(env->format[i]) || env->format[i] == ' ' ||
		env->format[i] == '.' || env->format[i] == '#' ||
		env->format[i] == '+' || env->format[i] == '-' ||
		env->format[i] == '*')
		return (1);
	else
		return (0);
}

static void		init_t_arg(t_arg *new)
{
	new->precision_is_set = 0;
	new->precision = 0;
	new->nb_of_zero = 0;
	new->min = 0;
	new->is_ptr = 0;
	new->modifier = M_DEFAULT;
	new->type = T_DEFAULT;
}

static void		default_padding(t_arg *arg, t_format *env,
									char buffer[BUF_SIZE])
{
	int			i;

	i = 0;
	if (!arg->flags.rev_pad)
		while (i < arg->min - 1)
		{
			if (arg->flags.zero_pad)
				put_char_in_buffer(env, '0', buffer);
			else
				put_char_in_buffer(env, ' ', buffer);
			i++;
		}
	put_char_in_buffer(env, env->format[env->position], buffer);
	if (arg->flags.rev_pad)
		while (i < arg->min - 1)
		{
			put_char_in_buffer(env, ' ', buffer);
			i++;
		}
}

void			parse_arg(t_format *env, va_list ap, char buffer[BUF_SIZE])
{
	t_arg		arg;

	env->nb_of_arg++;
	env->position++;
	init_t_arg(&arg);
	if (env->format[env->position] == '\0')
		return ;
	if (parse_arg_flags(env, &arg, 0) &&
		parse_arg_min(env, &arg, 0, ap) &&
		parse_arg_precision(env, &arg, 0, ap) &&
		parse_arg_modifier(env, &arg) &&
		parse_arg_type(env, &arg))
	{
		write_arg_in_buffer(env, ap, &arg, buffer);
	}
	else
	{
		if (env->format[env->position] == '\0')
			return ;
		default_padding(&arg, env, buffer);
		env->position++;
	}
	if (!env->is_error)
		env->cursor_error = env->written;
}
