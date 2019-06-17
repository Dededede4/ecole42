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

void			full_print_buffer(char buffer[BUF_SIZE])
{
	write(1, buffer, BUF_SIZE - 1);
}

void			final_print_buffer(char buffer[BUF_SIZE])
{
	size_t		len;

	len = 0;
	while (buffer[len] != '\0' || buffer[len + 1] != '\0')
		len++;
	write(1, buffer, len);
}

void			error_print_buffer(char buffer[BUF_SIZE], size_t written)
{
	write(1, buffer, written);
}
