#include "ft_printf.h"

void	ft_printf_putnbr_signed(int nbr, t_args a)
{
	(void)a;
	ft_putnbr(nbr);
}

void	ft_printf_putnbr_hexa_min(unsigned int nbr, t_args a)
{
	int	n;

	n = nbr % 16;
	if (nbr == 0)
		return;
	ft_printf_putnbr_hexa_min(nbr / 16, a);
	if (n >= 0 && n <= 9)
		ft_putchar('0' + n);
	if (n >= 10 && n <= 16)
		ft_putchar('a' + (n - 10));
}

void	ft_printf_putnbr_hexa_maj(unsigned int nbr, t_args a)
{
	int	n;

	n = nbr % 16;
	if (nbr == 0)
		return;
	ft_printf_putnbr_hexa_maj(nbr / 16, a);
	if (n >= 0 && n <= 9)
		ft_putchar('0' + n);
	if (n >= 10 && n <= 16)
		ft_putchar('A' + (n - 10));
}

void	ft_printf_putnbr_octal(unsigned int nbr, t_args a)
{
	int	n;

	n = nbr % 8;
	if (nbr == 0)
		return;
	ft_printf_putnbr_octal(nbr / 8, a);
	ft_putchar('0' + n);
}

void	ft_printf_putnbr_unsigned(unsigned int nbr, t_args a)
{
	int	n;

	n = nbr % 10;
	if (nbr == 0)
		return;
	ft_printf_putnbr_unsigned(nbr / 10, a);
	ft_putchar('0' + n);
}

void	ft_printf_putnbr_pointer(int *nbr, t_args a)
{
	(void)nbr;
	(void)a;
}