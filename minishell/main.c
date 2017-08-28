/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 12:41:15 by mprevot           #+#    #+#             */
/*   Updated: 2017/08/10 21:49:23 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		execute(char *command)
{
	char	**argv;
	char	*whereis;
	t_bool	isbuildin;

	argv = ft_strsplit(command, ' ');
	if (!argv || !argv[0])
	{
		ft_strsplit_del(&argv);
		return ;
	}
	whereis = ft_whereis(argv[0]);
	isbuildin = execbuiltin(argv);
	if (!isbuildin && !whereis)
	{
		ft_strdel(&whereis);
		ft_strsplit_del(&argv);
		ft_putstr_error("Command no found.\n");
		return ;
	}
	if (!isbuildin)
		ft_execwait(whereis, argv);
	ft_strdel(&whereis);
	ft_strsplit_del(&argv);
}

int			main(int argc, char **argv, char **environ)
{
	char *command;

	(void)argc;
	(void)argv;
	command = NULL;
	ft_loadenv(environ);
	while (42)
	{
		ft_printf("$> ");
		ft_gnl(STDIN_FILENO, &command);
		if (command && *command)
			execute(command);
		ft_strdel(&command);
	}
	exit(0);
}
