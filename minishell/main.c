/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 12:41:15 by mprevot           #+#    #+#             */
/*   Updated: 2017/08/06 13:00:32 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void		ft_execwait(char *path, char **av)
{
	pid_t	father;
	int		osef;

	osef = 0;
	father = fork();
	if (father > 0)
		wait(&osef);
	else
		execve(path, av, NULL);
}

void		putargv(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (NULL != argv[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

t_bool		execbuiltin(char **argv)
{
	int i;

	i = 0;
	if (ft_strequ(argv[0], "cd") && argv[1])
		chdir(argv[1]);
	else if (ft_strequ(argv[0], "exit"))
	{
		ft_strsplit_del(&argv);
		ft_delallenv();
		exit(0);
	}
	else if (ft_strequ(argv[0], "echo"))
		putargv(argv);
	else if (ft_strequ(argv[0], "setenv") && argv[1] && argv[2])
		ft_setenv(argv[1], argv[2], 1);
	else if (ft_strequ(argv[0], "export") && argv[1])
		ft_putenv(argv[1]);
	else if (ft_strequ(argv[0], "unsetenv") && argv[1])
		ft_delenv(argv[1]);
	else if (ft_strequ(argv[0], "env"))
		ft_displayenv();
	else
		return (FALSE);
	return (TRUE);
}

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
