/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ptr_in_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:59:19 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:46:40 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void			write_ptr_in_buffer(t_format *env, t_arg *arg, va_list ap,
									char buffer[BUF_SIZE])
{
	arg->modifier = L;
	arg->flags.alternate_form = 0;
	arg->type = L_HEXA;
	arg->min -= 2;
	arg->is_ptr = 1;
	write_hexa_in_buffer(env, arg, ap, buffer);
}
