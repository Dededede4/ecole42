/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:45:40 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 19:45:46 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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

void		log_and_chdir(char *path)
{
	char	*absolute;
	char	*save;

	if (!path)
		return ;
	save = ft_strdup(path);
	absolute = getcwd(ft_strnew(256), 256);
	ft_setenv("OLDPWD", absolute, TRUE);
	ft_strdel(&absolute);
	chdir(save);
	ft_strdel(&save);
	absolute = getcwd(ft_strnew(256), 256);
	ft_setenv("PWD", absolute, TRUE);
	ft_strdel(&absolute);
}

void		execbuiltin_cd(char **argv)
{
	if (!argv[1] && ft_getenv("HOME"))
		log_and_chdir(ft_getenv("HOME"));
	else if (ft_strequ(argv[1], "-"))
		log_and_chdir(ft_getenv("OLDPWD"));
	else if (argv[1])
		log_and_chdir(argv[1]);
}

t_bool		execbuiltin(char **argv)
{
	extern char	**environ;

	if (ft_strequ(argv[0], "cd"))
		execbuiltin_cd(argv);
	else if (ft_strequ(argv[0], "exit"))
	{
		ft_strsplit_del(&argv);
		ft_delallenv();
		t_restore();
		execve("/usr/bin/reset", (char *[15]){"/usr/bin/reset"}, environ);
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

void		del_argv(char **argv, int argc)
{
	int i;

	i = 0;
	while (i < argc)
	{
		ft_memdel((void**)&(argv[i]));
		i++;
	}
	free((void**)argv);
}
