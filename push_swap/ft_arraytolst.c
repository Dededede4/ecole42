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
	int		nbr;
	char	*strcmp;
	t_bool	r;

	nbr = ft_atoi(str);
	strcmp = ft_itoa(nbr);
	r = (ft_strcmp(strcmp, str) == 0);
	free(strcmp);
	return (r);
}

t_bool		ft_exist(int val, t_list *lst)
{
	while (lst)
	{
		if (*((int*)lst->content) == val)
			return (TRUE);
		lst = lst->next;
	}
	return (FALSE);
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
		val = ft_atoi(str[i]);
		if (!ft_test_intsyntax(str[i++]) || ft_exist(val, first))
		{
			ft_putstr_fd("Error\n", 1);
			exit(0);
		}
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
