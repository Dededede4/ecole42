/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrlen_spec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:07:35 by heynard           #+#    #+#             */
/*   Updated: 2017/06/22 18:14:42 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t		ft_strrlen_spec(const char *s, char spec)
{
	size_t	size;
	size_t	cursor;

	size = 0;
	cursor = 0;
	while (s[cursor] != '\0' && s[cursor] != spec)
		cursor += 1;
	if (s[cursor + 1] == '\0')
		return (cursor);
	cursor++;
	while (s[cursor + size] != '\0')
		size++;
	return (size);
}
