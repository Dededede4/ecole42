/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_str_in_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 13:59:21 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:46:57 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void			padding_str(t_format *env, t_arg *arg,
									char buffer[BUF_SIZE], int s)
{
	int				i;

	i = 0;
	if (arg->precision_is_set)
	{
		if (s < arg->precision)
			;
		else
			s = arg->precision;
	}
	while (arg->min - i > s)
	{
		if (arg->flags.zero_pad && !arg->flags.rev_pad)
			put_char_in_buffer(env, '0', buffer);
		else
			put_char_in_buffer(env, ' ', buffer);
		i++;
	}
}

void				write_str(t_format *env, t_arg *arg, char *to_print,
								char buffer[BUF_SIZE])
{
	size_t			i;

	i = 0;
	if (arg->precision_is_set)
	{
		while (to_print[i] != '\0' && (long int)i < arg->precision)
		{
			put_char_in_buffer(env, to_print[i], buffer);
			i++;
		}
	}
	else
	{
		while (to_print[i] != '\0')
		{
			put_char_in_buffer(env, to_print[i], buffer);
			i++;
		}
	}
}

void				write_str_in_buffer(t_format *env, t_arg *arg,
											va_list ap, char buffer[BUF_SIZE])
{
	char			*to_print;
	int				size;

	to_print = va_arg(ap, char *);
	size = ft_strlen(to_print);
	if (!arg->flags.rev_pad)
		padding_str(env, arg, buffer, size);
	if (to_print == NULL)
		write_str(env, arg, "(null)", buffer);
	else
		write_str(env, arg, to_print, buffer);
	if (arg->flags.rev_pad)
		padding_str(env, arg, buffer, size);
}
