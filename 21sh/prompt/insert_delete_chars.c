/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_delete_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 09:34:45 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/04 09:34:46 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void				ft_insert_char(
	unsigned int **str, unsigned int c, size_t pos)
{
	unsigned int	*begin;
	unsigned int	*end;
	unsigned int	*middle;

	middle = ft_memalloc(8);
	middle[0] = c;
	if (NULL == *str)
	{
		*str = middle;
		return ;
	}
	if ('\0' == ((unsigned int *)(*str))[pos])
	{
		begin = ft_uintdup(*str);
		ft_uintdel(str);
		*str = ft_uintjoin_multi(TRUE, begin, middle, NULL);
		return ;
	}
	begin = ft_uintdup_len((*str), pos);
	end = ft_uintdup((unsigned int*)(*str) + pos);
	ft_uintdel(str);
	*str = ft_uintjoin_multi(TRUE, begin, middle, end, NULL);
}

void				ft_delete_char(unsigned int **str, size_t pos)
{
	unsigned int	*begin;
	unsigned int	*end;
	size_t			len;

	if (NULL == *str)
		return ;
	len = ft_uintlen(*str);
	if (len < pos || 0 == len)
		return ;
	begin = ft_uintdup_len((*str), pos);
	if (len - 1 == pos)
	{
		ft_uintdel(str);
		*str = begin;
		return ;
	}
	end = ft_uintdup((unsigned int*)(*str) + pos + 1);
	free(*str);
	*str = ft_uintjoin_multi(TRUE, begin, end, NULL);
}
