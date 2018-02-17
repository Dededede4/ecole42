/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storeinstructs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 20:07:30 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 20:07:37 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	storeinstructs(t_instruct *instruct)
{
	static t_list *list = NULL;

	if (!list)
	{
		list = ft_lstnew(&instruct, sizeof(t_instruct*));
	}
	else
	{
		ft_lstadd(&list, ft_lstnew(&instruct, sizeof(t_instruct*)));
	}
}
