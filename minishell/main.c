#include "minishell.h"
#include <stdio.h>
void            ft_loadenv();

typedef struct			s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

extern char **environ;

t_env		**ft_env()
{
	static t_env	*l = NULL;
	static t_bool	first = TRUE;

	if (TRUE == first)
	{
		first = FALSE;
		ft_loadenv();
	}
	return (&l);		
}

void		ft_setenv(char *name, char *value, int overwrite)
{
	t_env	*env;
	t_env	**root;

	if(!(*(root = ft_env())))
	{
		env = ft_memalloc(sizeof(t_env));
		env->key = ft_strdup(name);
		env->value = ft_strdup(value);
		*root = env;
		return ;
	}		
	env = *root;
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0 && 0 == overwrite)
			return ;
		if (NULL == env->next)
		{
			env->next = ft_memalloc(sizeof(t_env));
			env->next->key = ft_strdup(name);
			env->next->value = ft_strdup(value);
			return;
		}
		env = env->next;
	}
}

void		ft_displayenv()
{
	t_env *env;

	env = *(ft_env());
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

char		*ft_getenv(char *name)
{
	t_env *env;

	env = *(ft_env());
	while (env)
	{
		if (ft_strcmp(name, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void		ft_delenv(char *name)
{
	t_env *env;
	t_env *tmp;
	t_env *prev;

	env = *(ft_env());
	while (env)
	{
		if (ft_strequ(name, env->key))
		{
			prev->next = env->next;
			ft_strdel(&env->key);
			ft_strdel(&env->value);
			ft_memdel((void**)&env);
			return ;	
		}
		prev = env;
		env = env->next;
	}
}

char		*ft_strdup_len(char *str, size_t len)
{
	size_t	i;
	char	*newstr;

	newstr = ft_strnew(len);
	ft_memcpy(newstr, str, len);
	return (newstr);
}

void		ft_putenv(char *str)
{
	char	*stop;
	char	*key;
	char	*value;

	if(!(stop = ft_strchr(str, '=')))
		return ;
	key = ft_strdup_len(str, (stop - str));
	value = ft_strdup(stop + 1);
	ft_setenv(key, value, TRUE);		
	ft_strdel(&key);
	ft_strdel(&value);
}

void		ft_loadenv()
{
	int i;

	i = 0;
	while(environ[i])
	{
		ft_putenv(environ[i]);
		i++;
	}
}

char		**command2argv(char *command)
{
	return ft_strsplit(command, ' ');
}

char		*ft_whereis(char *cmd_name)
{
	char	*path;
	char	**paths;
	char	*current;
	int	i;

	i = 0;
	path = ft_getenv("PATH");
	paths = ft_strsplit(path, ':');
	while (paths[i])
	{
		current = ft_strjoin_multi(FALSE, paths[i], "/", cmd_name, NULL);
		if (access(current, X_OK) == 0)
			break ;
		ft_strdel(&current);
		i++;
	}
	// TODO : leaks
	return (current);
}


void		ft_execwait(char *path, char **av)
{
	pid_t	father;
	int	osef;

	osef = 0;
	father = fork();
	if (father > 0)
	{
		wait(&osef);
	}
	else
	{
		execve(path, av, NULL);
	}
}

t_bool		execbuiltin(char **argv)
{
	if (ft_strequ(argv[0], "cd") && argv[1])
		chdir(argv[1]);
	else if(ft_strequ(argv[0], "exit"))
		exit(0);
	else if(ft_strequ(argv[0], "echo"))
		ft_putendl(argv[1]);
	else if(ft_strequ(argv[0], "setenv") && argv[1] && argv[2])
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
	char **argc;
	char *whereis;
	t_bool	isbuildin;

	argc = command2argv(command);
	if (!argc[0])
		return ;
	whereis = ft_whereis(argc[0]);
	isbuildin = execbuiltin(argc);
	if (!isbuildin && !whereis)
	{
		ft_putstr_error("Command no found.\n");
		return ;
	}
	if (!isbuildin)
		ft_execwait(whereis, argc);
	// echo ; setenv ; unsetenv ; env t

}

int		main(int argc, char **argv)
{
	char *command;

	command = NULL;
	while (42)
	{
		ft_printf("$>");
		ft_gnl(STDIN_FILENO, &command);
		execute(command);
		ft_strdel(&command);
	}
	exit(0);
}
