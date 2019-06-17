/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:13:19 by heynard           #+#    #+#             */
/*   Updated: 2018/12/13 22:31:07 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void			ft_reset_buffer(t_format *env, char buffer[BUF_SIZE])
{
	size_t		i;

	i = 0;
	if (env->written == BUF_SIZE - 1)
		full_print_buffer(buffer);
	while (i < BUF_SIZE)
	{
		buffer[i] = '\0';
		i++;
	}
	env->print += env->written;
	env->written = 0;
}

static void		pf_error(t_format *env, char buffer[BUF_SIZE])
{
	if (env->nb_of_arg > 0)
		error_print_buffer(buffer, env->cursor_error);
	env->print = -1;
}

static void		inner_printf(va_list ap, t_format *env)
{
	char		buffer[BUF_SIZE];

	ft_reset_buffer(env, buffer);
	while (env->format[env->position] != '\0')
	{
		if (env->format[env->position] == '%')
			parse_arg(env, ap, buffer);
		else
		{
			buffer[env->written] = env->format[env->position];
			env->position++;
			env->written++;
		}
		if (env->is_error)
		{
			pf_error(env, buffer);
			return ;
		}
		if (env->written == BUF_SIZE - 1)
			ft_reset_buffer(env, buffer);
	}
	env->print += env->written;
	final_print_buffer(buffer);
}

int				ft_printf(const char *format, ...)
{
	t_format	env;
	va_list		ap;

	env.print = 0;
	if (!format)
		return (1);
	env.nb_of_arg = 0;
	env.cursor_error = 0;
	env.is_error = 0;
	env.format = format;
	env.written = 0;
	env.position = 0;
	va_start(ap, format);
	inner_printf(ap, &env);
	va_end(ap);
	return (env.print);
}
