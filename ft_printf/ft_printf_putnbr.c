void	ft_printf_putnbr_hexa_min(int nbr, t_args a)
{
	int	n;

	n = nbr % 16;
	if (n >= 0 && n <= 9)
		ft_putchar('0' + n);
	if (n >= 10 && n <= 16)
		ft_putchar('a' + (n - 10));
	n = nbr / 16;
	if (n == 0)
		return;
	return ft_printf_putnbr_hexa_min(n, a);
}