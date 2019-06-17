/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_wchar_in_buffer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:05:47 by heynard           #+#    #+#             */
/*   Updated: 2017/05/12 10:57:01 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t		get_len_wchar(wchar_t chr)
{
	if (chr < 0 || (chr >= 55296 && chr <= 57343))
		return (0);
	if (chr <= 0x7F)
		return (1);
	if (MB_CUR_MAX <= 1)
		return (0);
	if (chr <= 0x7FF)
		return (2);
	if (MB_CUR_MAX <= 2)
		return (0);
	if (chr <= 0xFFFF)
		return (3);
	if (MB_CUR_MAX <= 3)
		return (0);
	if (chr <= 0x10FFFF)
		return (4);
	return (0);
}

static void			padding_wchar(t_format *env, t_arg *arg,
									char buffer[BUF_SIZE], wchar_t c)
{
	int				i;

	i = 0;
	while (arg->min - i > size_of_wchar(c))
	{
		if (arg->flags.zero_pad && !arg->flags.rev_pad)
			put_char_in_buffer(env, '0', buffer);
		else
			put_char_in_buffer(env, ' ', buffer);
		i++;
	}
}

int					size_of_wchar(wchar_t c)
{
	if (c <= 0xFF)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else if (c <= 0x10FFFF)
		return (4);
	return (0);
}

void				write_wchar(t_format *env, wchar_t chr,
								char buffer[BUF_SIZE])
{
	if (chr <= 0x7F)
		put_char_in_buffer(env, chr, buffer);
	else if (chr <= 0x7FF)
	{
		put_char_in_buffer(env, (chr >> 6) + 0xC0, buffer);
		put_char_in_buffer(env, (chr & 0x3F) + 0x80, buffer);
	}
	else if (chr <= 0xFFFF)
	{
		put_char_in_buffer(env, (chr >> 12) + 0xE0, buffer);
		put_char_in_buffer(env, ((chr >> 6) & 0x3F) + 0x80, buffer);
		put_char_in_buffer(env, (chr & 0x3F) + 0x80, buffer);
	}
	else if (chr <= 0x10FFFF)
	{
		put_char_in_buffer(env, (chr >> 18) + 0xF0, buffer);
		put_char_in_buffer(env, ((chr >> 12) & 0x3F) + 0x80, buffer);
		put_char_in_buffer(env, ((chr >> 6) & 0x3F) + 0x80, buffer);
		put_char_in_buffer(env, (chr & 0x3F) + 0x80, buffer);
	}
}

void				write_wchar_in_buffer(t_format *env, t_arg *arg,
											va_list ap, char buffer[BUF_SIZE])
{
	wchar_t			to_print;
	size_t			len;

	to_print = (wchar_t)va_arg(ap, wint_t);
	len = get_len_wchar(to_print);
	arg->min -= len;
	if (len == 0)
		env->is_error = 1;
	if (!arg->flags.rev_pad)
		padding_wchar(env, arg, buffer, to_print);
	write_wchar(env, to_print, buffer);
	if (arg->flags.rev_pad)
		padding_wchar(env, arg, buffer, to_print);
}
