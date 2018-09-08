/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 22:14:43 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 22:14:57 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void		ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void			ft_putstr(char const *s)
{
	while (*s)
		ft_putchar_fd(*(s++), 1);
}

static int		ft_putstr_debug(char const *s)
{
	if (DEBUG_MALLOC)
		ft_putstr(s);
	return (1);
}

static int		pd(char const *s)
{
	if (DEBUG_MALLOC)
		ft_putstr(s);
	return (1);
}
