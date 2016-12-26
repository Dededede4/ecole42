#include "libft/libft.h"

#include <stdarg.h>

int	ft_recursive_printf(const char *str, va_list ap)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != '%')
	{
		ft_putchar(str[i]);
		i++;
	}
	if (str[i] == '%')
	{
		if (str[i + 1] == '%')
		{
			ft_putchar('%');
			i += 2;
		}
		else if (str[i + 1] == 's')
		{
			ft_putstr(va_arg(ap, char *));
			i += 2;
		}
		else if (str[i + 1] == 'd' || str[i + 1] == 'i')
		{
			ft_putnbr(va_arg(ap, int));
			i += 2;
		}
		ft_recursive_printf(str + i, ap);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	ft_recursive_printf(format, ap);

	va_end(ap);
	return (0);
}
