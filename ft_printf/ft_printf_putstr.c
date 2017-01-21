#include "ft_printf.h"

int			ft_putstr_utf8(t_unicode *str, int precision)
{
	size_t	size;
	char	*output;
	int		len;

	output = (char *)ft_unicode2utf8(str, &size);
	if (output == NULL)
		return -1;
	len = (precision < 1) ? size : precision - 1;
	write(1, output, len);
	free(output);
	return len;
}

int			ft_putstr_ascii(t_unicode *str, int precision)
{
	int		i;
	int		len;

	i = 0;
	len = (precision < 1) ? ft_unicodelen(str) : precision;
	while (str[i] && i < len)
	{
		ft_putchar(*(str + i));
		i++;
	}
	return i;
}


int			ft_putstr_raw_utf8(t_unicode *str, int precision)
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
	ft_putstr_utf8(str, precision);
	str[i] = old;
	if (str[i] == L'\n')
		write(1, "\\n", 2);
	else if (str[i] != L'\0')
		return ft_putstr_raw_utf8(str + i + 1, precision) + i;
	return i + 1;
}

int			ft_putstr_raw_ascii(t_unicode *str, int precision)
{
	return ft_putstr_raw_utf8(str, precision); // TODO
}

void	ft_printf_wputstr(t_unicode *str, t_args *a, int (*f)(t_unicode *, int))
{
	size_t	spaces;
	int		size;

	size = (int)ft_strsize(str);
	spaces = (a->width > size) ? a->width - size : 0;
	if (a->width != -1 && a->minus == -1)
	{
		if (str[0] != 0 && a->precision != -1)
			spaces = (a->width > size) ? a->width - a->precision : 0;
		if (str[0] == 0 && a->type == 'c')
		{
			spaces--;
			a->width--;
		}
		while (spaces--)
			ft_putchar((a->zero != -1) ? '0' : ' ');
	}
	size = f(str, a->precision);
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

