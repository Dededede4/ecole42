/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 20:57:02 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 20:57:04 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static size_t	show_alloc_mem_list(char *name, t_list **container)
{
	t_list	*current;
	size_t	total;

	total = 0;
	current = *container;
	ft_putstr(name);
	ft_putstr(" : 0x");
	ft_putnbr_fd_hexa((size_t)*container, 1);
	ft_putstr("\n");
	while (current)
	{
		ft_putstr("0x");
		ft_putnbr_fd_hexa((size_t)current->data, 1);
		ft_putstr(" - 0x");
		ft_putnbr_fd_hexa((size_t)(current->data + current->data_size), 1);
		ft_putstr(" : ");
		ft_putnbr_fd((size_t)(current->data_size), 1);
		ft_putstr("\n");
		total += current->data_size;
		current = current->next;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	size_t	total;

	total = show_alloc_mem_list("TINY", &g_container.tiny);
	total += show_alloc_mem_list("SMALL", &g_container.small);
	total += show_alloc_mem_list("LARGE", &g_container.large);
	ft_putstr("Total : ");
	ft_putnbr_fd(total, 1);
	ft_putstr(" octets\n");
}
