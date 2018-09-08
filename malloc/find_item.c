/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 22:23:58 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 22:24:41 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_list	*find_item_list(void *addr, t_list **page_container)
{
	t_list	*current;

	current = *page_container;
	while (current)
	{
		if (current->data == addr)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

static t_list	*find_item(void *addr)
{
	t_list	*r;

	if ((r = find_item_list(addr, &g_container.tiny)))
		return (r);
	if ((r = find_item_list(addr, &g_container.small)))
		return (r);
	if ((r = find_item_list(addr, &g_container.large)))
		return (r);
	return (NULL);
}
