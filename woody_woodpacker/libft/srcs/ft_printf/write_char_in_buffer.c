/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_char_in_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:39:11 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:46:12 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void			padding_char(t_format *env, t_arg *arg,
									char buffer[BUF_SIZE])
{
	int				i;

	i = 0;
	while (arg->min - i > 1)
	{
		if (arg->flags.zero_pad && !arg->flags.rev_pad)
			put_char_in_buffer(env, '0', buffer);
		else
			put_char_in_buffer(env, ' ', buffer);
		i++;
	}
}

void				write_char_in_buffer(t_format *env, t_arg *arg,
											va_list ap, char buffer[BUF_SIZE])
{
	unsigned char	to_print;

	to_print = (unsigned char)va_arg(ap, int);
	if (!arg->flags.rev_pad)
		padding_char(env, arg, buffer);
	if (to_print == 0)
		put_char_in_buffer(env, 0, buffer);
	else
		put_char_in_buffer(env, to_print, buffer);
	if (arg->flags.rev_pad)
		padding_char(env, arg, buffer);
}
