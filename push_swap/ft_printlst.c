/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 16:36:30 by mprevot           #+#    #+#             */
/*   Updated: 2017/02/08 16:36:31 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_printlst_item(t_list *lst)
{
	ft_printf("%d ", *((int*)lst->content));
}

void	ft_printlst_item_str(t_list *lst)
{
	ft_printf("%s\n", ((char*)lst->content));
}

void	ft_printlst(t_list *lst)
{
	ft_lstiter(lst, ft_printlst_item);
}

void	ft_printlst_str(t_list *lst)
{
	ft_lstiter(lst, ft_printlst_item_str);
}
