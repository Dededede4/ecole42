/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 17:58:40 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/03/28 00:27:21 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "script.h"

static int	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

static void	same_path(t_env *e, int argc, char **argv)
{
	if (argc != 4)
		ft_error("Error");
	e->dump = ft_atoi(argv[2]);
}

static void	tunnel(t_env *e, int argc, char **argv)
{
	if (!ft_strcmp(argv[1], "-all"))
	{
		e->dump = ft_atoi(argv[2]);
		if (!e->dump)
			ft_error("Error");
		run_test_all(e);
	}
	else if (!ft_strcmp(argv[1], "-unit"))
	{
		same_path(e, argc, argv);
		e->dump = ft_atoi(argv[3]);
		if (!e->str_unit || !e->dump)
			ft_error("Error");
		run_test_unit(e);
	}
	else if (!ft_strcmp(argv[1], "-rd"))
	{
		same_path(e, argc, argv);
		e->nb_test = ft_atoi(argv[3]);
		if (!e->dump || !e->nb_test)
			ft_error("Error");
		run_test_rd(e);
	}
	else
		ft_error("Error");
}

int			main(int argc, char **argv)
{
	t_env	e;
	int		i;

	i = 0;
	if (argc <= 2)
	{
		ft_printf("./debug -all [dump]\n./debug -unit [\"champ/1.cor ...\"]");
		ft_printf(" [dump]\n./debug -rd [dump] [nb_test]\n");
		return (0);
	}
	init_env(&e, argv);
	tunnel(&e, argc, argv);
	return (0);
}
