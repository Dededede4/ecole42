#include "ft_printf.h"

void	ft_printf_putstr(const char *str, t_args a)
{
	int	i;

	i = 0;
	if (a.precision == -1)
		ft_putstr(str);
	else
	{
		while (str[i] && i < a.precision)
			i++;
		write(1, str, i);
	}
}

void	ft_printf_wputstr(wchar_t *str, t_args a)
{
	int	i;

	i = 0;
	while (str[i] && i < a.precision)
		i++;
	write(1, str, i);
}

void	ft_printf_putchar(char c, t_args a)
{
	(void)c;
	(void)a;
}