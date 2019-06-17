/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 17:22:13 by heynard           #+#    #+#             */
/*   Updated: 2017/06/19 17:22:14 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t		ft_strlen_spec(const char *s, char spec)
{
	size_t	size;

	size = 0;
	while (s[size] != '\0' && s[size] != spec)
		size += 1;
	return (size);
}
