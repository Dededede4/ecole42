#include "ft_printf.h"

int			ft_putstr_utf8(t_unicode *str, size_t len)
{
	size_t	size;
	char	*output;

	output = (char *)ft_unicode2utf8(str, &size);
	if (output == NULL)
		return -1;
	write(1, output, len + (size - len));
	free(output);
	return size;
}

int			ft_putstr_ascii(t_unicode *str, size_t len)
{
	int		i;

	i = 0;
	len--;
	while (i < (int)len)
		ft_putchar((char)str[i++]);
	return i;
}


int			ft_putstr_raw_utf8(t_unicode *str, size_t len)
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
	ft_putstr_utf8(str, len);
	str[i] = old;
	if (str[i] == L'\n')
		write(1, "\\n", 2);
	else if (str[i] != L'\0')
		return ft_putstr_raw_utf8(str + i + 1, len) + i;
	return i + 1;
}

int			ft_putstr_raw_ascii(t_unicode *str, size_t len)
{
	return ft_putstr_raw_utf8(str, len); // TODO
}

void	ft_printf_wputstr(t_unicode *str, t_args *a, int (*f)(t_unicode *, size_t))
{
	size_t	spaces;
	size_t len;
	int		size;


	len = 0;
	size = 0;
	if (a->precision == -1)
		while (str[len])
			len++;
	else
		while (str[len] && len < (size_t)a->precision)
			len++;
	spaces = (a->width > (int)len) ? a->width - len : 0;
	a->tmp = len;
	if (a->width != -1 && a->minus == -1)
	{
		if (str[0] == 0)
		{
			spaces--;
			a->width--;
		}
		while (spaces--)
			ft_putchar((a->zero != -1) ? '0' : ' ');
	}
	size = f(str, len + 1) - a->tmp;
	a->tmp += size;
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

