#include "ft_printf.h"
#include <stdio.h>

void	ft_printf_wputstr(wchar_t *str, t_args a)
{
	size_t	i;
	size_t len;

	len = 0;
	if (a.precision == -1)
		while (str[len])
			len++;
	else
		while (str[len] && len < (size_t)a.precision)
			len++;
	i = a.width - len;
	if (a.width != -1 && a.minus == -1)
		while (i--)
			ft_putchar(' ');
	write(1, str, len * sizeof(wchar_t));
	if (a.width != -1 && a.minus != -1)
		while (i--)
			ft_putchar(' ');
}


void	ft_printf_putchar(char c, t_args a)
{
	(void)a;
	ft_putchar(c);
}