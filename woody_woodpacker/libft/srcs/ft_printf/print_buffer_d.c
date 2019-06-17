/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 20:36:03 by heynard           #+#    #+#             */
/*   Updated: 2017/05/11 22:45:41 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void			full_print_buffer_d(char buffer[BUF_SIZE], t_format *env)
{
	write(env->fd, buffer, BUF_SIZE - 1);
}

void			final_print_buffer_d(char buffer[BUF_SIZE], t_format *env)
{
	size_t		len;

	len = 0;
	while (buffer[len] != '\0' || buffer[len + 1] != '\0')
		len++;
	write(env->fd, buffer, len);
}

void			error_print_buffer_d(char buffer[BUF_SIZE], size_t written,
									t_format *env)
{
	write(env->fd, buffer, written);
}
