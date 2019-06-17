/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_wide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 17:05:47 by heynard           #+#    #+#             */
/*   Updated: 2017/04/01 17:05:58 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t				ft_strlen_wide(const wchar_t *original)
{
	const wchar_t	*end;

	end = original;
	while (*end != '\0')
		end++;
	return (end - original);
}
