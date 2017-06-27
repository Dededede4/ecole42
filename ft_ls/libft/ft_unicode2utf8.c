/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode2utf8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 19:19:47 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/24 19:19:53 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_charsize(t_unicode c)
{
	if ((int)c < 128)
		return (1);
	else if ((int)c < 2048)
		return (2);
	else if ((int)c < 65536)
		return (3);
	else if ((int)c < 2097152)
		return (4);
	else
		return (5);
}

size_t			ft_strsize(t_unicode *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		size += ft_charsize(str[i]);
		i++;
	}
	return (size);
}

int				ft_unicodemask(size_t chars)
{
	if (chars == 2)
		return (0xC080);
	else if (chars == 3)
		return (0xE08080);
	else if (chars == 4)
		return (0xF0808080);
	return (0);
}

int				ft_utf8int(t_unicode c)
{
	size_t		chars;
	int			nbr;
	t_unicode	save;
	int			to_write;

	save = c;
	chars = ft_charsize(c);
	if (chars == 1)
	{
		return (int)c;
	}
	else
	{
		nbr = ft_unicodemask(chars);
		to_write = 0x3F;
		while (chars--)
		{
			nbr = (nbr | (save & to_write));
			save = save << 2;
			to_write = to_write << 8;
		}
		return (nbr);
	}
}

t_utf8			*ft_unicode2utf8(t_unicode *i_str, size_t *size)
{
	t_utf8		*c_str;
	size_t		i;
	int			nbr;
	size_t		maxbytes;
	size_t		chars;

	i = 0;
	maxbytes = *size;
	*size = 0;
	if (!(c_str = (t_utf8*)ft_strnew(ft_strsize(i_str) + 1)))
		return (NULL);
	while (i_str[i])
	{
		chars = ft_charsize(i_str[i]);
		nbr = ft_utf8int(i_str[i]);
		if (*size + chars > maxbytes)
			return (c_str);
		(*size) += chars;
		while (chars--)
			c_str[(*size) - chars - 1] = (t_utf8)(nbr >> (8 * (chars)));
		i++;
	}
	return (c_str);
}
