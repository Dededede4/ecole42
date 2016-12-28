#include "ft_printf.h"

uintmax_t	ft_printf_getarg_nbr_unsigned(va_list args, t_args a)
{
	uintmax_t	nbr;

	nbr = va_arg(args, uintmax_t);
	if (a.lenght == SIZE_HH)
		nbr = (unsigned char)nbr;
	else if (a.lenght == SIZE_H)
		nbr = (unsigned short int)nbr;
	else if (a.lenght == SIZE_L)
		nbr = (unsigned long int)nbr;
	else if (a.lenght == SIZE_LL)
		nbr = (unsigned long long int)nbr;
	else if (a.lenght == SIZE_J)
		nbr = (uintmax_t)nbr;
	else if (a.lenght == SIZE_Z)
		nbr = (size_t)nbr;
	else if (a.type == 'p')
		nbr = (unsigned long)nbr;
	else
		nbr = (unsigned int)nbr;
	return (nbr);
}

void	ft_printf_putnbr_unsigned(uintmax_t nbr, t_args a, char base)
{
	uintmax_t	n;

	a.tmp++;
	if (nbr == 0)
	{
		if(a.hash != -1)
		{
			ft_putchar('0');
			a.tmp++;
			if (base == 16)
				ft_putchar('x');
		}
		if (a.precision != -1)
		{
			n = a.precision - a.tmp;
			while(n--)
				write(1, "0", 1);
		}
		return;
	}
	ft_printf_putnbr_unsigned(nbr / base, a, base);
	n = nbr % base;
	if (n <= 9)
		ft_putchar('0' + n);
	if (n >= 10 && n <= 36)
	{
		if (a.type == 'X')
			ft_putchar('A' + (n - 10));
		else
			ft_putchar('a' + (n - 10));
	}
}


intmax_t	ft_printf_getarg_nbr_signed(va_list args, t_args a)
{
	intmax_t	nbr;

	nbr = va_arg(args, uintmax_t);
	if (a.lenght == SIZE_HH)
		nbr = (signed char)nbr;
	else if (a.lenght == SIZE_H)
		nbr = (short int)nbr;
	else if (a.lenght == SIZE_L)
		nbr = (long int)nbr;
	else if (a.lenght == SIZE_LL)
		nbr = (long long int)nbr;
	else if (a.lenght == SIZE_J)
		nbr = (intmax_t)nbr;
	else if (a.lenght == SIZE_Z)
		nbr = (ssize_t)nbr;
	else
		nbr = (int)nbr;
	return (nbr);
}

void	ft_printf_putnbr_signed(intmax_t nbr, t_args a, char base, int neg)
{
	intmax_t	n;

	a.tmp++;
	if (nbr == 0)
	{
		if (neg)
		{
			ft_putchar('-');
			a.tmp++;
		}
		if (a.precision != -1)
		{
			n = a.precision - a.tmp;
			while(n--)
				write(1, "0", 1);
		}
		return;
	}
	ft_printf_putnbr_signed(nbr / base, a, base, neg);
	n = nbr % base;
	if (neg)
		n = 0 - n;
	if (n <= 9)
		ft_putchar('0' + n);
	if (n >= 10 && n <= 36)
	{
		if (a.type == 'X')
			ft_putchar('A' + (n - 10));
		else
			ft_putchar('a' + (n - 10));
	}
}