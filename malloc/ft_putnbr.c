/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 22:13:34 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 22:14:36 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_putnbr_fd(size_t n, int fd)
{
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		ft_putchar_fd(n + '0', fd);
	}
}

static void	ft_putnbr_fd_hexa(size_t n, int fd)
{
	if (n >= 16)
	{
		ft_putnbr_fd_hexa(n / 16, fd);
		ft_putnbr_fd_hexa(n % 16, fd);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd(n + '0', fd);
		else
			ft_putchar_fd((n - 10) + 'A', fd);
	}
}

static void	ft_putnbr_fd_debug(size_t n, int fd)
{
	if (DEBUG_MALLOC)
		ft_putnbr_fd(n, fd);
}
