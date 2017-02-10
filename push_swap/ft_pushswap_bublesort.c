/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushswap_bublesort.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 19:39:52 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/10 19:39:53 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			ft_lstmove(t_list **lst, size_t len)
{
	size_t		i;
	t_list		*first;
	t_list		*current;
	t_list		*before_current;

	if (len == 0)
		return ;
	i = 0;
	first = *lst;
	current = first;
	before_current = NULL;
	while (current)
	{
		if (i == len)
		{
			*lst = current;
			if (before_current)
				before_current->next = NULL;
		}
		i++;
		before_current = current;
		current = current->next;
	}
	before_current->next = first;
}

int				ft_pushswap_bublesort_findsup(t_vals *vals, int start)
{
	t_vals		*ovals;
	int			i;
	int			p_val;
	size_t		len;
	int			tmp;

	i = 0;
	ovals = ft_lstcpy(vals);
	len = ft_lstlen(vals);
	ft_lstmove(&ovals, (size_t)start);
	p_val = *((int*)ovals->content);
	while (ovals)
	{
		if (p_val > *((int*)ovals->content))
		{
			tmp = (((i) + start) % (int)len);
			tmp = ((tmp <= ((int)len / 2) ? tmp - 1 : ((0 - (int)len) + tmp)));
			return (tmp);
		}
		p_val = *((int*)ovals->content);
		i++;
		ovals = ovals->next;
	}
	return (-2000000);
}

void			ft_pushswap_bublesort_onmove(
	t_stacks *stacks, int len, int moves, int *index)
{
	int			savemoves;

	savemoves = moves;
	while (moves != 0)
	{
		if (moves > 0)
			ft_pushswap_instruct(INSTRUCT_RA, stacks);
		else if (moves < 0)
			ft_pushswap_instruct(INSTRUCT_RRA, stacks);
		moves += (moves > 0) ? -1 : 1;
	}
	ft_pushswap_instruct(INSTRUCT_SA, stacks);
	if (savemoves < 0)
	{
		*index = *index - savemoves;
		*index = *index % len;
	}
	else if (savemoves > 0)
	{
		*index = (*index + (len - savemoves)) % len;
	}
}

t_stacks		*ft_pushswap_bublesort(t_vals *vals)
{
	t_stacks	*stacks;
	int			moves;
	int			index;
	int			len;

	stacks = malloc(sizeof(t_stacks));
	stacks->stacka = ft_lstcpy(vals);
	stacks->instructs = NULL;
	stacks->stackb = NULL;
	len = (int)ft_lstlen(vals);
	index = 0;
	while ((moves = ft_pushswap_bublesort_findsup(stacks->stacka, index))
			!= -2000000)
		ft_pushswap_bublesort_onmove(stacks, len, moves, &index);
	while (index--)
	{
		ft_pushswap_instruct(INSTRUCT_RA, stacks);
		vals = vals->next;
	}
	return (stacks);
}
