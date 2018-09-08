/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_pages.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 22:15:39 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 22:15:52 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void display_pages(){
	t_list *current;
	size_t poid;

	ft_putstr("====== DÉBUT ======\n");
	current = g_container.tiny;
	poid = 0;
	while(current)
	{
		if (current->is_new_page)
		{
			if(poid != 0)
			{
				ft_putstr("Total : ");
				ft_putnbr_fd(poid, 1);
				ft_putstr(" octets\n");
				poid = 0;
			}
			ft_putstr("\n\nNouvelle page :\n");
		}
		ft_putnbr_fd_hexa((size_t)current, 1);
		ft_putstr(" Bloc de ");
		ft_putnbr_fd(current->data_size, 1);
		ft_putstr(" octets\n");
		poid += current->data_size + sizeof(t_list);
		current = current->next;
	}
	ft_putstr("Poid restant : ");
	ft_putnbr_fd(poid, 1);
	ft_putstr(" octets\n");
}
