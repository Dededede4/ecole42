/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bin_in_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 18:14:30 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:46:00 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static uintmax_t	get_arg_bin(t_arg *arg, va_list ap)
{
	uintmax_t		to_print;

	to_print = va_arg(ap, uintmax_t);
	if (arg->modifier == HH)
		to_print = (unsigned char)to_print;
	if (arg->modifier == H)
		to_print = (unsigned short int)to_print;
	if (arg->modifier == Z)
		to_print = (size_t)to_print;
	if (arg->modifier == M_DEFAULT)
		to_print = (unsigned int)to_print;
	return (to_print);
}

static void			write_bin(t_format *env, t_arg *arg,
							uintmax_t nb, char buffer[BUF_SIZE])
{
	if (arg->precision_is_set && nb == 0 && arg->precision == 0)
		return ;
	if (nb / 2 <= 0)
	{
		put_char_in_buffer(env, (char)((nb % 2) + 48), buffer);
		return ;
	}
	else
	{
		write_bin(env, arg, nb / 2, buffer);
		put_char_in_buffer(env, (char)((nb % 2) + 48), buffer);
	}
}

static void			inner_write_bin(uintmax_t to_print, t_format *env,
										t_arg *arg, char buffer[BUF_SIZE])
{
	int				i;
	int				nbc;

	i = 0;
	nbc = ft_count_base_nb(to_print, 2) + arg->nb_of_zero;
	if (arg->flags.alternate_form && (to_print != 0 || arg->precision_is_set))
	{
		put_char_in_buffer(env, '0', buffer);
		put_char_in_buffer(env, 'b', buffer);
	}
	while (arg->precision - i > nbc)
	{
		i++;
		put_char_in_buffer(env, '0', buffer);
	}
	if (!arg->flags.rev_pad && arg->flags.zero_pad)
		padding_int(env, arg, buffer, to_print);
	write_bin(env, arg, to_print, buffer);
	if (arg->flags.rev_pad)
		padding_int(env, arg, buffer, to_print);
}

void				write_bin_in_buffer(t_format *env, t_arg *arg,
											va_list ap, char buffer[BUF_SIZE])
{
	uintmax_t		to_print;

	to_print = get_arg_bin(arg, ap);
	if (arg->precision_is_set)
		arg->flags.zero_pad = 0;
	arg->min -= (arg->flags.alternate_form) ? 2 : 0;
	if (!arg->flags.rev_pad && !arg->flags.zero_pad)
		padding_int(env, arg, buffer, to_print);
	inner_write_bin(to_print, env, arg, buffer);
}
