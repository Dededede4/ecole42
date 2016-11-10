/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_alphabet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:01:43 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/10 13:44:48 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_putchar(char c);

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
}

int		ft_is_superior_str(char *a, char *b)
{
	int		i;

	i = 0;
	while (a[i] == b[i] && a[i] > '\0' && b[i] < '\0')
	{
		i++;
	}
	if (a[i] <= b[i])
		return (0);
	return (1);
}

void	ft_bublesort_str(int count, char **list)
{
	char	*tmp;
	int		i;

	i = 1;
	while (i < (count - 1))
	{
		if (ft_is_superior_str(list[i], list[i + 1]))
		{
			tmp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	int i;

	i = 1;
	ft_bublesort_str(argc, argv);
	while (i < argc)
	{
		ft_putstr(argv[i]);
		ft_putchar('\n');
		i++;
	}
	return (0);
}
