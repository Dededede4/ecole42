/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_wstr_in_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:32:51 by heynard           #+#    #+#             */
/*   Updated: 2017/05/12 10:57:11 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t		ft_wstrlen_prec(t_format *env, wchar_t *str,
										int precision, size_t i)
{
	if (*str < 0 || *str > 0x10FFFF || (*str >= 55296 && *str <= 57343))
		env->is_error = 1;
	if (*str == '\0' || precision == 0)
		return (i);
	else if (*str <= 0x7F)
		return (ft_wstrlen_prec(env, str + 1, precision - 1, i + 1));
	if (MB_CUR_MAX <= 1)
		env->is_error = 1;
	if (*str <= 0x7FF && precision >= 2)
		return (ft_wstrlen_prec(env, str + 1, precision - 2, i + 2));
	if (MB_CUR_MAX <= 2)
		env->is_error = 1;
	if (*str <= 0xFFFF && precision >= 3)
		return (ft_wstrlen_prec(env, str + 1, precision - 3, i + 3));
	if (MB_CUR_MAX <= 3)
		env->is_error = 1;
	if (*str <= 0x10FFFF && precision >= 4)
		return (ft_wstrlen_prec(env, str + 1, precision - 4, i + 4));
	return (i);
}

static size_t		ft_wstrlen(t_format *env, wchar_t *str)
{
	long int		i;

	i = 0;
	while (*str)
	{
		if (*str < 0 || *str > 0x10FFFF || (*str >= 55296 && *str <= 57343))
			env->is_error = 1;
		if (*str <= 0x7F)
			i++;
		else if (*str <= 0x7FF)
			i += 2;
		else if (*str <= 0xFFFF)
			i += 3;
		else if (*str <= 0x10FFFF)
			i += 4;
		if (*str <= 0x7FF && MB_CUR_MAX <= 1)
			env->is_error = 1;
		else if (*str <= 0xFFFF && MB_CUR_MAX <= 2)
			env->is_error = 1;
		else if (*str <= 0x10FFFF && MB_CUR_MAX <= 3)
			env->is_error = 1;
		str++;
	}
	return (i);
}

static void			padding_wstr(t_format *env, t_arg *arg,
									char buffer[BUF_SIZE], size_t size)
{
	int				limit;
	int				i;

	i = 0;
	if (arg->precision_is_set && arg->precision == 0)
		limit = 0;
	else
		limit = (int)(!arg->precision_is_set ? size :
					arg->precision - (arg->precision % size));
	while (arg->min - i > limit)
	{
		if (arg->flags.zero_pad && !arg->flags.rev_pad)
			put_char_in_buffer(env, '0', buffer);
		else
			put_char_in_buffer(env, ' ', buffer);
		i++;
	}
}

static void			write_wstr(t_format *env, t_arg *arg, wchar_t *str,
								char buffer[BUF_SIZE])
{
	long int		i;

	i = 0;
	if (arg->precision_is_set)
	{
		while (*str && i < arg->precision)
		{
			i += size_of_wchar(*str);
			if (i > arg->precision)
				return ;
			write_wchar(env, *str, buffer);
			str++;
		}
	}
	else
	{
		while (*str)
		{
			write_wchar(env, *str, buffer);
			str++;
		}
	}
}

void				write_wstr_in_buffer(t_format *env, t_arg *arg, va_list ap,
											char buffer[BUF_SIZE])
{
	wchar_t			*str;
	size_t			len;

	str = va_arg(ap, wchar_t *);
	if (str != NULL)
		len = arg->precision_is_set ?
			ft_wstrlen_prec(env, str, arg->precision, 0) : ft_wstrlen(env, str);
	else
		len = 6;
	if (!arg->flags.rev_pad)
		padding_wstr(env, arg, buffer, len);
	if (str == NULL)
		write_str(env, arg, "(null)", buffer);
	else
		write_wstr(env, arg, str, buffer);
	if (arg->flags.rev_pad)
		padding_wstr(env, arg, buffer, len);
}
