#include "ft_printf.h"

size_t	ft_wputstr(t_unicode *str)
{
	size_t	size;

	char *output = (char *)ft_unicode2utf8(str, &size);
	write(1, output, size);
	free(output);
	return size;
}

void	ft_printf_wputstr(t_unicode *str, t_args *a)
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
	a->tmp += ft_wputstr(str) - a->tmp;
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
			write(fd, "\\n", 2);
		}
		else
			write(fd, finded, 1);
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
