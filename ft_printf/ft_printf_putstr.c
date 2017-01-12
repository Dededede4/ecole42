#include "ft_printf.h"

int			ft_putstr_utf8(t_unicode *str)
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

int			ft_putstr_ascii(t_unicode *str)
{
	int		i;

	i = 0;
	while (str[i])
		ft_putchar((char)str[i++]);
	return i;
}


int			ft_putstr_raw_utf8(t_unicode *str)
{
	size_t			i;
	t_unicode		old;

	i = 0;
	if (*str == L'\0')
		return i;
	while (str[i] && str[i] != L'\n')
		i++;
	old = str[i];
	str[i] = 0;
	ft_putstr_utf8(str);
	str[i] = old;
	if (str[i] == L'\n')
		write(1, "\\n", 2);
	else if (str[i] != L'\0')
		return ft_putstr_raw_utf8(str + i + 1) + i;
	return i + 1;
}

int			ft_putstr_raw_ascii(t_unicode *str)
{
	return ft_putstr_raw_utf8(str); // TODO
}

void	ft_printf_wputstr(t_unicode *str, t_args *a, int (*f)(t_unicode *))
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
	size = f(str) - a->tmp;
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

