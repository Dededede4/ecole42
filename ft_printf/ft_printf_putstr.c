#include "ft_printf.h"
#include <stdio.h>

size_t		ft_charsize(t_unicode c)
{
	if ((int)c < 128)
		return 1;
	else if ((int)c < 2048)
		return 2;
	else if ((int)c < 65536)
		return 3;
	else if ((int)c < 2097152)
		return 4;
	else
		return 5;
}

size_t		ft_strsize(t_unicode *str)
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


t_utf8		*ft_unicode2utf8(t_unicode *i_str, size_t *size)
{
	t_utf8	*c_str;
	size_t	i;

	i = 0;
	*size = 0;
	if (!(c_str = (t_utf8*)ft_strnew(ft_strsize(i_str))))
		return (NULL);
	while (i_str[i])
	{
		size_t chars = ft_charsize(i_str[i]);
		int		nbr;
		int		save = i_str[i];
		nbr = 0;
		if (chars == 1)
		{
			c_str[*size] = (t_utf8)i_str[i];
			i++;
			(*size)++;
			continue;
		}
		else if (chars == 2)
			nbr = 0xC080;
		else if (chars == 3)
			nbr = 0xE08080;
		else if (chars == 4)
			nbr = 0xF0808080;
		int 	toWrite = 0x3F;
		while (chars--)
		{
			nbr = (nbr | (save & toWrite));			
			save = save << 2;
			toWrite = toWrite << 8;
		}
		chars = ft_charsize(i_str[i]);
		(*size) += chars;
		while (chars--)
			c_str[(*size) - chars] = (t_utf8)(nbr >> (8 * chars));
		(*size)++;
		i++;		
	}
	return c_str;
}

void	ft_wputstr(t_unicode *str)
{
	size_t	size;

	char *output = (char *)ft_unicode2utf8(str, &size);
	write(1, output, size);
	free(output);
}

void	ft_printf_wputstr(wchar_t *str, t_args *a)
{
	size_t	spaces;
	size_t len;

	len = 0;
	if (a->precision == -1)
		while (str[len])
			len++;
	else
		while (str[len] && len < (size_t)a->precision)
			len++;
	spaces = a->width - len;
	if (a->width != -1)
		a->tmp = a->width;
	else
		a->tmp = len;
	if (a->width != -1 && a->minus == -1)
		while (spaces--)
			ft_putchar(' ');
	ft_wputstr(str);
	if (a->width != -1 && a->minus != -1)
		while (spaces--)
			ft_putchar(' ');
}

int		ft_printf_not_printable(void *s)
{
	wchar_t c;

	c = *((wchar_t*)s);
	if (c == L'\n')
	{
		return (1);
	}
	return (0);
}

void	ft_rwwrite(int fd, wchar_t *str, size_t len)
{
	wchar_t		*finded;

	if (*str == L'\0')
		return;
	finded = ft_memchrf(str, ft_printf_not_printable, len * 4);
	if (finded == NULL)
	{
		write(fd, str, len * sizeof(wchar_t));
	}
	else
	{
		write(fd, str, (finded - str) * 4);
		if (*finded == L'\n')
		{
			write(fd, L"\\n", 8);
		}
		else
			write(fd, finded, 4);
		ft_rwwrite(fd, finded + 1, len - 1 - ((finded - str)));
	}
}

void	ft_printf_rwputstr(wchar_t *str, t_args *a)
{
	size_t	spaces;
	size_t len;

	len = 0;
	if (a->precision == -1)
		while (str[len])
			len++;
	else
		while (str[len] && len < (size_t)a->precision)
			len++;
	spaces = a->width - len;
	if (a->width != -1)
		a->tmp = a->width;
	else
		a->tmp = len;
	if (a->width != -1 && a->minus == -1)
		while (spaces--)
			ft_putchar(' ');
	ft_rwwrite(1, str, len);
	if (a->width != -1 && a->minus != -1)
		while (spaces--)
			ft_putchar(' ');
}
