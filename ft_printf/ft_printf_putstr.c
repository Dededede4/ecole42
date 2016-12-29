#include "ft_printf.h"
#include <stdio.h>

void	ft_printf_wputstr(t_args *a)
{
	// Ajouter  dans le t_args
	size_t len;

	len = 0;
	if (a->precision == -1)
		while (str[len])
			len++;
	else
		while (str[len] && len < (size_t)a->precision)
			len++;
	
	if (a->width != -1)
		a->tmp = a->width;
	else
		a->tmp = len;
	write(1, str, len * sizeof(wchar_t));
}

void	ft_printf_putargs(t_args *a, char (*f)(t_args *))
{
	size_t spaces;

	spaces = a->width - len;
	if (a->width != -1 && a->minus == -1)
		while (spaces--)
			ft_putchar(' ');
	f(a);
	if (a->width != -1 && a->minus != -1)
		while (spaces--)
			ft_putchar(' ');
}

