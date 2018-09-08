/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 20:06:54 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 20:06:56 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void		*ft_realloc_afterchecks(void *ptr, size_t size)
{
	void	*new;
	t_list	*item;

	new = ft_malloc(size);
	item = find_item(ptr);
	if (DEBUG_MALLOC)
		write(1, "\x1B[31mft_realloc(", 16);
	if (NULL == item)
	{
		if (DEBUG_MALLOC)
			ft_putnbr_fd(size, 1);
		return (NULL);
	}
	if (DEBUG_MALLOC)
	{
		ft_putnbr_fd(item->data_size, 1);
		ft_putstr(" ");
		ft_putnbr_fd(size, 1);
	}
	ft_memcpy(new, ptr, item->data_size < size ? item->data_size : size);
	if (DEBUG_MALLOC)
		write(1, ");\x1B[0m\n", 7);
	ft_free(ptr);
	return (new);
}

static void		*ft_realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	return (ft_realloc_afterchecks(ptr, size));
}
