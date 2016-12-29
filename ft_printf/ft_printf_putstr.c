#include "ft_printf.h"
#include <stdio.h>

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
	write(1, str, len * sizeof(wchar_t));
	if (a->width != -1 && a->minus != -1)
		while (spaces--)
			ft_putchar(' ');
}
