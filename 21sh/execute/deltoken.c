/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deltoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:33:44 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 19:33:53 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_token		*deltoken(t_token **delme)
{
	t_token		*next;

	if (delme && *delme)
	{
		next = (*delme)->next;
		ft_memdel((void**)&((*delme)->str));
	}
	else
		next = NULL;
	ft_memdel((void**)delme);
	*delme = NULL;
	return (next);
}
