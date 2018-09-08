/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_page_large.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 22:26:09 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 22:26:21 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_list	*malloc_page_large(size_t size)
{
	t_list		*current;
	static char	first = 0;

	if (!first)
	{
		g_container.large = NULL;
		g_container.nbr_large = 0;
		first = 1;
	}
	g_container.nbr_large++;
	if (g_container.large)
	{
		current = g_container.large;
		while (current->next)
		{
			current = current->next;
		}
		current->next = malloc_direct(size);
		return (current->next);
	}
	else
	{
		g_container.large = malloc_direct(size);
		return (g_container.large);
	}
}
