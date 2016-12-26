void	ft_printf_wputstr(wchar_t *str, t_args a)
{
	int	i;

	i = 0;
	while (str[i] && i < a.precision)
		i++;
	write(1, str, i);
}