/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 22:27:31 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 22:27:45 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_malloc(size_t size)
{
	void *ret;

	if (DEBUG_MALLOC)
	{
		write(1, "\x1B[31mmalloc(", 12);
		ft_putnbr_fd(size, 1);
		write(1, ");\x1B[0m\n", 7);
	}
	if (size == 0)
		return (NULL);
	if ((size * 4) <= getpagesize() - sizeof(t_list))
		ret = malloc_list(size, &g_container.tiny);
	else if (size <= getpagesize() - sizeof(t_list))
		ret = malloc_list(size, &g_container.small);
	else
		ret = malloc_large(size);
	return (ret);
}
