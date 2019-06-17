/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arg_in_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 19:56:56 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:45:52 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void		write_percent_in_buffer(t_format *env,
										t_arg *arg, char buffer[BUF_SIZE])
{
	int			i;

	i = 0;
	if (arg->flags.rev_pad)
		buffer[env->written++] = '%';
	if (env->written == BUF_SIZE)
		ft_reset_buffer(env, buffer);
	if (arg->min > 1)
		while (i < arg->min - 1)
		{
			if (arg->flags.zero_pad && !arg->flags.rev_pad)
				buffer[env->written++] = '0';
			else
				buffer[env->written++] = ' ';
			if (env->written == BUF_SIZE)
				ft_reset_buffer(env, buffer);
			i++;
		}
	if (!arg->flags.rev_pad)
		buffer[env->written++] = '%';
	if (env->written == BUF_SIZE)
		ft_reset_buffer(env, buffer);
}

void			put_char_in_buffer(t_format *env,
									char to_print, char buffer[BUF_SIZE])
{
	buffer[env->written] = to_print;
	env->written++;
	if (env->written == BUF_SIZE - 1)
		ft_reset_buffer(env, buffer);
}

void			write_arg_in_buffer(t_format *env, va_list ap,
									t_arg *arg, char buffer[BUF_SIZE])
{
	if (arg->type == PERCENT)
		write_percent_in_buffer(env, arg, buffer);
	else if (arg->type == S_DEC)
		write_sint_in_buffer(env, arg, ap, buffer);
	else if (arg->type == U_DEC)
		write_uint_in_buffer(env, arg, ap, buffer);
	else if (arg->type == L_HEXA || arg->type == U_HEXA)
		write_hexa_in_buffer(env, arg, ap, buffer);
	else if (arg->type == OCTAL)
		write_octal_in_buffer(env, arg, ap, buffer);
	else if (arg->type == U_CHAR && arg->modifier != L)
		write_char_in_buffer(env, arg, ap, buffer);
	else if (arg->type == STRING && arg->modifier != L)
		write_str_in_buffer(env, arg, ap, buffer);
	else if (arg->type == PTR)
		write_ptr_in_buffer(env, arg, ap, buffer);
	else if (arg->type == U_CHAR && arg->modifier == L)
		write_wchar_in_buffer(env, arg, ap, buffer);
	else if (arg->type == STRING && arg->modifier == L)
		write_wstr_in_buffer(env, arg, ap, buffer);
	else if (arg->type == U_BIN)
		write_bin_in_buffer(env, arg, ap, buffer);
}
