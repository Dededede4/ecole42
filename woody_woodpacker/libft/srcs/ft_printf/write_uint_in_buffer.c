/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_uint_in_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 21:47:37 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:47:14 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static uintmax_t	get_arg_uint(t_arg *arg, va_list ap)
{
	uintmax_t		to_print;

	to_print = va_arg(ap, uintmax_t);
	if (arg->modifier == HH)
		to_print = (unsigned char)to_print;
	if (arg->modifier == H)
		to_print = (unsigned short int)to_print;
	if (arg->modifier == M_DEFAULT)
		to_print = (unsigned int)to_print;
	return (to_print);
}

static void			write_uint(t_format *env, t_arg *arg,
							uintmax_t to_print, char buffer[BUF_SIZE])
{
	if (arg->precision_is_set && to_print == 0 && arg->precision == 0)
		return ;
	if (to_print / 10 <= 0)
	{
		put_char_in_buffer(env, (char)(to_print % 10 + 48), buffer);
		return ;
	}
	else
	{
		write_uint(env, arg, to_print / 10, buffer);
		put_char_in_buffer(env, (char)(to_print % 10 + 48), buffer);
	}
}

static void			inner_write_uint(uintmax_t to_print, t_format *env,
										t_arg *arg, char buffer[BUF_SIZE])
{
	int				i;
	int				nbc;

	i = 0;
	nbc = ft_count_nb(to_print) + arg->nb_of_zero;
	while (arg->precision - i > nbc)
	{
		i++;
		put_char_in_buffer(env, '0', buffer);
	}
	if (!arg->flags.rev_pad && arg->flags.zero_pad)
		padding_int(env, arg, buffer, to_print);
	write_uint(env, arg, to_print, buffer);
	if (arg->flags.rev_pad)
		padding_int(env, arg, buffer, to_print);
}

void				write_uint_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE])
{
	uintmax_t		to_print;

	to_print = get_arg_uint(arg, ap);
	if (arg->precision_is_set)
		arg->flags.zero_pad = 0;
	if (!arg->flags.rev_pad && !arg->flags.zero_pad)
		padding_int(env, arg, buffer, to_print);
	inner_write_uint(to_print, env, arg, buffer);
}
