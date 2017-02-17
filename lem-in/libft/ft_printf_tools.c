/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:14:13 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/25 16:14:15 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_printf_synonyms(t_args *a)
{
	if (a->type == 'D')
	{
		a->type = 'd';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'O')
	{
		a->type = 'o';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'U')
	{
		a->type = 'u';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'C')
	{
		a->type = 'c';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'S')
	{
		a->type = 's';
		a->lenght = SIZE_L;
	}
}

int					ft_printf_return(int new_return)
{
	static int		old_return = 0;

	if (old_return == -1 && PERSIST_RETURN)
		return (-1);
	old_return = new_return;
	return (new_return);
}

t_unicode			*ft_wstrdup(const unsigned char *str, size_t len)
{
	t_unicode		*r;

	if (!(r = malloc((len + 1) * sizeof(t_unicode))))
		return (NULL);
	r[len] = '\0';
	while (len--)
		r[len] = str[len];
	return (r);
}
