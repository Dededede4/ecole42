#include "ft_printf.h"

int			ft_wputstr(t_unicode *str)
{
	size_t	size;
	char	*output;

	output = (char *)ft_unicode2utf8(str, &size);
	if (output == NULL)
		return -1;
	write(1, output, size);
	free(output);
	return size;
}

void	ft_printf_wputstr(t_unicode *str, t_args *a)
{
	size_t	spaces;
	size_t len;
	int		size;


	len = 0;
	if (a->precision == -1)
		while (str[len])
			len++;
	else
		while (str[len] && len < (size_t)a->precision)
			len++;
	spaces = (a->width > (int)len) ? a->width - len : 0;
	a->tmp = len;
	if (a->width != -1 && a->minus == -1)
		while (spaces--)
			ft_putchar(' ');
	size = ft_wputstr(str) - a->tmp;
	a->tmp += size;
	if (a->width != -1 && spaces > 0)
		a->tmp = a->width;
	if (size == -1)
		a->err = 1;
	if (a->width != -1 && a->minus != -1)
		while (spaces--)
			ft_putchar(' ');
	a->tmp = (a->tmp == 0) ? 1 : a->tmp;
}


void	ft_rwwrite(t_unicode *str)
{
	size_t			i;
	t_unicode		old;

	i = 0;
	if (*str == L'\0')
		return;
	while (str[i] && str[i] != L'\n')
		i++;
	old = str[i];
	str[i] = 0;
	ft_wputstr(str);
	str[i] = old;
	if (str[i] == L'\n')
		write(1, "\\n", 2);
	else if (str[i] != L'\0')
		ft_rwwrite(str + i + 1);
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
	spaces = (a->width > (int)len) ? a->width - len : 0;
	if (a->width != -1)
		a->tmp = a->width;
	else
		a->tmp = len;
	if (a->width != -1 && a->minus == -1)
		while (spaces--)
			ft_putchar(' ');
	ft_rwwrite(str);
	if (a->width != -1 && a->minus != -1)
		while (spaces--)
			ft_putchar(' ');
}
