/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 09:48:59 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/04 11:37:02 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_printf(const char *format, ...)
{
	va_list			ap;
	int				r;

	va_start(ap, format);
	r = ft_vprintf(format, ap);
	va_end(ap);
	return (r);
}

int					ft_printf_return(int new_return)
{
	static int		old_return = 0;

	if (old_return == -1 && PERSIST_RETURN)
		return (-1);
	old_return = new_return;
	return (new_return);
}

int					ft_vprintf(const char *restrict str, va_list ap)
{
	int				i;
	char			*tmp;
	t_args			a;
	int				printed;

	i = 0;
	if (str == NULL)
		return (-1);
	tmp = ft_strchr(str, '%');
	if (tmp == NULL)
	{
		ft_putstr(str);
		return (ft_printf_return((int)ft_strlen(str)));
	}
	i = tmp - str;
	write(1, str, i);
	a = ft_printf_readarg(str + i);
	ft_printf_synonyms(&a);
	if (ft_printf_execarg(&a, ap) == 0)
		return (0);
	printed = i + a.tmp;
	i += a.nbr;
	if (a.err == 1)
		return (ft_printf_return(-1));
	return (ft_printf_return(ft_vprintf(str + i, ap) + printed));
}

void				ft_printf_synonyms(t_args *a)
{
	if (a->type == 'D')
	{
		a->type = 'd';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'O')
	{
		a->type = 'o';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'U')
	{
		a->type = 'u';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'C')
	{
		a->type = 'c';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'S')
	{
		a->type = 's';
		a->lenght = SIZE_L;
	}
}

t_unicode			*ft_wstrdup(const unsigned char *str, size_t len)
{
	t_unicode		*r;

	if (!(r = malloc((len + 1) * sizeof(t_unicode))))
		return (NULL);
	r[len] = '\0';
	while (len--)
		r[len] = str[len];
	return (r);
}
