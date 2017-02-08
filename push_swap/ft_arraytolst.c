/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraytolst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:42:05 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/08 13:42:07 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bool		ft_test_intsyntax(char *str)
{
	int nbr;

	nbr = ft_atoi(str);
	return (ft_atoi(ft_itoa(nbr)) == nbr);
}

t_list		*ft_arraytolst(char **str, int size)
{
	t_list	*first;
	t_list	*current;
	int		val;
	int		i;

	i = 0;
	first = NULL;
	while (i < size)
	{
		if (!ft_test_intsyntax(str[i]))
		{
			ft_putstr_fd("Error\n", 1);
			exit(0);
		}
		val = ft_atoi(str[i++]);
		if (first == NULL)
		{
			first = ft_lstnew(&val, sizeof(int));
			current = first;
			continue ;
		}
		current->next = ft_lstnew(&val, sizeof(int));
		current = current->next;
	}
	return (first);
}
