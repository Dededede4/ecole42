/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_sint_in_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 14:37:30 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:46:49 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static intmax_t	get_arg_sint(t_arg *arg, va_list ap)
{
	intmax_t	to_print;

	to_print = va_arg(ap, intmax_t);
	if (arg->modifier == HH)
		to_print = (char)to_print;
	else if (arg->modifier == H)
		to_print = (short int)to_print;
	else if (arg->modifier == M_DEFAULT)
		to_print = (int)to_print;
	return (to_print);
}

void			padding_int(t_format *env, t_arg *arg,
								char buffer[BUF_SIZE],
								intmax_t to_print)
{
	int			nbc;

	if (arg->type == U_HEXA || arg->type == L_HEXA)
		nbc = ft_count_base_nb(to_print, 16) + arg->nb_of_zero;
	else if (arg->type == OCTAL)
		nbc = ft_count_base_nb(to_print, 8) + arg->nb_of_zero;
	else if (arg->type == U_BIN)
		nbc = ft_count_base_nb(to_print, 2) + arg->nb_of_zero;
	else
		nbc = ft_count_nb(to_print) + arg->nb_of_zero;
	if (arg->precision_is_set && to_print == 0 && arg->precision == 0)
		nbc = 0;
	while (arg->min > (arg->precision > nbc ? arg->precision : nbc))
	{
		arg->min--;
		if (arg->flags.zero_pad && !arg->flags.rev_pad
			&& !arg->precision_is_set)
			put_char_in_buffer(env, '0', buffer);
		else
			put_char_in_buffer(env, ' ', buffer);
	}
}

static void		write_sint(t_format *env, t_arg *arg,
							intmax_t to_print, char buffer[BUF_SIZE])
{
	int			tmp;

	tmp = arg->nb_of_zero;
	if (arg->precision_is_set && to_print == 0 && arg->precision == 0)
		return ;
	while (to_print / 10 > 0)
	{
		put_char_in_buffer(env, (char)(to_print % 10 + 48), buffer);
		to_print /= 10;
	}
	put_char_in_buffer(env, (char)(to_print + 48), buffer);
	while (arg->nb_of_zero)
	{
		put_char_in_buffer(env, '0', buffer);
		arg->nb_of_zero--;
	}
	arg->nb_of_zero = tmp;
}

static void		inner_write_sint(intmax_t to_print, t_format *env, t_arg *arg,
									char buffer[BUF_SIZE])
{
	int			nbc;
	int			i;

	i = 0;
	nbc = ft_count_nb(to_print) + arg->nb_of_zero;
	if (!arg->neg)
	{
		if (arg->flags.force_sign)
		{
			arg->flags.add_space = 0;
			put_char_in_buffer(env, '+', buffer);
		}
		else if (arg->flags.add_space)
			put_char_in_buffer(env, ' ', buffer);
	}
	while (arg->precision - i > nbc)
	{
		i++;
		put_char_in_buffer(env, '0', buffer);
	}
	if (!arg->flags.rev_pad && arg->flags.zero_pad)
		padding_int(env, arg, buffer, to_print);
	write_sint(env, arg, to_print, buffer);
	if (arg->flags.rev_pad)
		padding_int(env, arg, buffer, to_print);
}

void			write_sint_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE])
{
	intmax_t	to_print;

	arg->neg = 0;
	to_print = get_arg_sint(arg, ap);
	if (to_print < 0)
	{
		arg->neg = 1;
		to_print *= -1;
	}
	if (to_print == -9223372036854775807 - 1)
		to_print = 8085774586302733229;
	else
		to_print = ft_rev_nbr(to_print, &(arg->nb_of_zero));
	if (arg->precision_is_set)
		arg->flags.zero_pad = 0;
	arg->min -= (arg->flags.add_space ||
						arg->flags.force_sign || arg->neg) ? 1 : 0;
	if (!arg->flags.rev_pad && !arg->flags.zero_pad)
		padding_int(env, arg, buffer, to_print);
	if (arg->neg)
	{
		arg->flags.add_space = 0;
		put_char_in_buffer(env, '-', buffer);
	}
	inner_write_sint(to_print, env, arg, buffer);
}
