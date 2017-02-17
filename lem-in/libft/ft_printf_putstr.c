/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:33:24 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/24 18:33:31 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_putstr_utf8(
	t_unicode *str, t_args *a)
{
	size_t		size;
	char		*output;
	size_t		len;
	size_t		spaces;

	len = (a->precision > 0) ? a->precision : -1;
	if (a->precision == 0 && a->type != 'u')
		len = 0;
	size = len;
	output = (char *)ft_unicode2utf8(str, &size);
	if (output == NULL)
		return (-1);
	spaces = (a->precision > (int)size && a->width > 0) ?
		a->precision - size : 0;
	while (spaces--)
		ft_putchar(' ');
	write(1, output, size);
	free(output);
	return (size);
}

int				ft_putstr_ascii(
	t_unicode *str, t_args *a)
{
	int			i;
	int			len;
	size_t		size;

	i = 0;
	size = ft_unicodelen(str);
	len = (a->precision < (int)size && a->precision > 0)
		? a->precision : (int)size;
	if (a->precision == 0 && a->type != 'u')
		len = 0;
	while (str[i] && i < len)
	{
		ft_putchar(*(str + i));
		i++;
	}
	return (i);
}

int				ft_putstr_raw_utf8(
	t_unicode *str, t_args *a)
{
	size_t		i;
	t_unicode	old;

	i = 0;
	if (*str == L'\0')
		return (i);
	while (str[i] && str[i] != L'\n')
		i++;
	old = str[i];
	str[i] = 0;
	ft_putstr_utf8(str, a);
	str[i] = old;
	if (str[i] == L'\n')
		write(1, "\\n", 2);
	else if (str[i] != L'\0')
		return (ft_putstr_raw_utf8(str + i + 1, a) + i);
	return (i + 1);
}

int				ft_putstr_raw_ascii(t_unicode *str, t_args *a)
{
	return (ft_putstr_raw_utf8(str, a));
}

void			ft_printf_wputstr(
	t_unicode *str, t_args *a, int (*f)(t_unicode *, t_args *a))
{
	size_t		spaces;
	int			size;

	spaces = ft_printf_putstr_printwidth(str, a);
	size = f(str, a);
	a->tmp = size;
	if (a->width != -1 && spaces > 0 && a->width > a->tmp)
		a->tmp = a->width;
	if (size == -1)
		a->err = 1;
	if (a->width != -1 && a->minus != -1)
		while (spaces--)
			ft_putchar(' ');
	if (str[0] == '\0' && a->type == 'c')
	{
		ft_putchar('\0');
		a->tmp++;
	}
}
