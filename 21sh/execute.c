#include "main.h"
#include <unistd.h>
void ft_uintput(unsigned int *str);
unsigned int	*ft_uintnew(size_t size);
char *ft_uint_to_char(unsigned int *input);
char 	*display_input_heredoc(char *stop);

char		*ft_memdup(char *mem, size_t len)
{
	char	*newalloc;
	size_t	i;

	i = 0;
	newalloc = ft_memalloc(len + 4);
	while (i < len)
	{
		newalloc[i] = mem[i];
		i++;
	}
	return newalloc;
}

unsigned int	*ft_uintsub(unsigned int const *s, unsigned int start, size_t len)
{
	unsigned int	*str;

	if (!s)
		return (NULL);
	str = ft_uintnew(len);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, (void*)(s + start), len * 4);
	return (str);
}

unsigned int	*ft_uinttrim(unsigned int const *s)
{
	size_t	d;
	size_t	f;

	if (!s)
		return (NULL);
	d = 0;
	while (s[d] == ' ' || s[d] == '\t' || s[d] == '\n')
		d++;
	if (s[d] == '\0')
		return (ft_uintnew(0));
	f = ft_uintlen(s) - 1;
	while (s[f] == ' ' || s[f] == '\t' || s[f] == '\n')
		f--;
	return (ft_uintsub(s, d, f - d + 1));
}

unsigned int		*ft_uinttrim_free(unsigned int **str)
{
	unsigned int	*tmp;

	tmp = ft_uinttrim(*str);
	ft_memdel((void**)str);
	return (tmp);
}

size_t	get_word_pos(unsigned int *str, size_t start)
{
	size_t	i;
	char	quote;

	i = start;
	quote = '\0';
	while (str[i])
	{
		if ('\'' == str[i] || '"' == str[i])
		{
			if (i > 0 && '\\' == str[i - 1])
			{
				// escapé
			}
			else if ('\0' == quote)
			{				// début
				quote = str[i];
			}
			else if (str[i] == (unsigned int)quote) // fin
			{
				quote = '\0';
			}
			else
			{
				// au milieu
			}
		}
		if ('\t' == str[i + 1] || ' ' == str[i + 1] || ';' == str[i + 1] || '>' == str[i + 1] ||  '<' == str[i + 1] || '|' == str[i + 1])
		{
			if (!quote)
			{
				return i;
			}
		}
		if ('\t' == str[i] || ' ' == str[i] || ';' == str[i] || '>' == str[i] ||  '<' == str[i] || '|' == str[i])
		{
			if (!quote)
			{
				return i;
			}
		}
		i++;
	}
	return (i); // TODO ERREUR
}

unsigned int *clear_escapes_startend(unsigned int **str)
{
	unsigned int *cpy;
	unsigned int *tmp;
	int i;

	if ('\'' != (*str)[0] && '"' != (*str)[0])
	{
		tmp = ft_uintdup((*str));
		ft_memdel((void**)str);
		return tmp;
	}
	// On retire le premier
	i = 0;
	cpy = ft_uintdup((*str));
	while((*str)[i + 1])
	{
		cpy[i] = (*str)[i + 1];
		i++;
	}
	// On retire le dernier
	cpy[i - 1] = '\0';
	ft_memdel((void**)str);
	return cpy;

}

unsigned int *clear_escapes(unsigned int *str)
{
	size_t			original_i;
	size_t			new_i;

	original_i = 0;
	new_i	   = 0;
	while (str[original_i])
	{
		if (!str[original_i + 1])
		{
			break;
		}
		if('\\' == str[original_i])
		{
			if ('\\' == str[original_i + 1] ||
				('"' == str[original_i + 1] && '\'' != str[0]) ||
				('\'' == str[original_i + 1] && '"' != str[0] ))
			{
				original_i++;
			}
		}
		str[new_i] = str[original_i];
		original_i++;
		new_i++;
	}
	str[new_i] = str[original_i];
	str[new_i + 1] = '\0';
	if (new_i > 2)
	{
		return clear_escapes_startend(&str);
	}
	else
	{
		return str;
	}
}

t_token		*tokenize(unsigned int *str) // todo char **;
{
	// il faudra copier-coller ça afin de compter tout ce qu'on veut
	size_t			i;
	size_t			stop;
	t_token			*token;
	t_token			*first_token;
	size_t			len;
	char 			*strchar;

	i = 0;
	token = NULL;
	first_token = NULL;
	if (!str || !*str)
		return (NULL);
	len = ft_uintlen(str);
	while(i < len)
	{
		if (' ' != str[i] && '\t' != str[i])
		{
			stop = get_word_pos(str, i);
			if (NULL == token)
			{
				token = ft_memalloc(sizeof(*token));
				first_token = token;
			}
			else
			{
				token->next = ft_memalloc(sizeof(*token));
				token = token->next;
			}
			strchar = (char*)str;
			token->str = (unsigned int *)ft_memdup(strchar + (i * 4), (stop - i + 1) * 4);
			token->str = ft_uinttrim_free(&(token->str));
			token->str = clear_escapes(token->str);
			
			i = stop + 1;
		}
		else
			i++;
	}
	return (first_token);
}

int		ft_uintcmp(unsigned int *s1, unsigned int *s2)
{
	int i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return ((int)((unsigned int)s1[i] - (unsigned int)s2[i]));
}

int			ft_atoi_uint(const unsigned int *str)
{
	int		result;
	int		n;

	n = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v' \
			|| *str == ' ' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		n = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	result = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		result = (result * 10) - (*str - '0');
		str++;
	}
	if (n)
		return (result);
	else
		return (0 - result);
}

int 		heredoc(char *stop)
{
	char *str;
	int p[2];

	pipe(p);
	str = display_input_heredoc(stop);
	free(stop);
	ft_putstr_fd(str, p[1]);
	ft_strdel(&str);
	close(p[1]);
	return p[0];
}

t_token *deltoken(t_token **delme)
{
	t_token *next;

	if(delme && *delme)
	{
		next = (*delme)->next;
		ft_memdel((void**)&((*delme)->str));
	}
	else
		next = NULL;
	ft_memdel((void**)delme);
	*delme = NULL;
	return next;
}

t_token *test = NULL;

t_instruct *command2instruct(t_command *command)
{
	t_instruct	*instruct;
	t_instruct	*first_instruct;
	t_instruct *tmpinstruct;
	t_token		*token;
	t_token		*arg;
	t_token		*lastarg;


	arg = NULL;
	token = tokenize(command->str);
	if (!token)
		return NULL; // ?
	instruct = ft_memalloc(sizeof(*instruct));
	instruct->pipe_to_fd = dup(1);
	instruct->program_name = ft_uintdup(token->str);
	first_instruct = instruct;

	token = deltoken(&token);
	while(token)
	{
		if (0 == ft_uintcmp(token->str, (unsigned int *)L";"))
		{
			if (token->next)
			{
				arg = NULL;
				token = deltoken(&token);
				instruct->next = ft_memalloc(sizeof(*instruct));
				instruct->pipe_to_fd = dup(1);
				instruct = instruct->next;
				instruct->program_name = ft_uintdup(token->str);
			}
			else
				break;
			// fin de la commande
		}
		else // un argument normal
		{
			if (!arg)
			{
				arg = ft_memalloc(sizeof(*arg));
				instruct->program_args = arg;
			}
			else
			{
				arg->next = ft_memalloc(sizeof(*arg));
				arg = arg->next;
			}
			arg->str = ft_uintdup(token->str);
		}
		token = deltoken(&token);
	}

	// Maintenant on va convertir les redirections

	instruct = first_instruct;
	while(instruct)
	{
		arg = instruct->program_args;
		lastarg = NULL;
		while (arg && arg->next)
		{
			if (arg->ignore_me)
			{
				arg = arg->next;
				continue;
			}
			// On va noter les >>
			if ('>' == *arg->str && '>' == *arg->next->str)
			{
				if (arg->next->next){
					instruct->pipe_to_file = ft_uint_to_char(arg->next->next->str);
					arg->next->next->ignore_me = TRUE;
				}
				
				instruct->replace_file = FALSE;
				if (lastarg && 0 == ft_uintcmp(lastarg->str, (unsigned int *)L"2"))
				{
					instruct->aggregate_fd = TRUE;
					lastarg->ignore_me = TRUE;
				}

				arg->ignore_me = TRUE;
				arg->next->ignore_me = TRUE;
				
			}
			
			// On note les <<
			
			/*ft_uintput(arg->next->str);
			ft_putstr("<--");*/
			if ('<' == *arg->str && '<' == *arg->next->str)
			{
				arg->ignore_me = TRUE;
				arg->next->ignore_me = TRUE;
				
				if (arg->next->next)
				{
					instruct->pipe_from_fd = heredoc(ft_uint_to_char(arg->next->next->str));
					arg->next->next->ignore_me = TRUE;
				}
				else
					instruct->pipe_from_fd = heredoc(ft_strdup("<<"));
				// TODO il faut une fonction de type ft_uinttoi
				/*if (!arg->next->next){} // TODO error
				instruct->pipe_form_fd = arg->next->next->str;*/
			}
			

			// on note les >
			if ('>' == *arg->str && '>' != *arg->next->str)
			{
				if (!arg->next){} // TODO error
				if (lastarg && 0 == ft_uintcmp(lastarg->str, (unsigned int *)L"2"))
				{
					instruct->aggregate_fd = TRUE;
					lastarg->ignore_me = TRUE;
				}
				instruct->pipe_to_file = ft_uint_to_char(arg->next->str);//
				instruct->replace_file = TRUE;
				arg->ignore_me = TRUE;
				arg->next->ignore_me = TRUE;
			}

			// on note les <
			if ('<' == *arg->str && '<' != *arg->next->str)
			{
				if (!arg->next->next){} // TODO error
				instruct->pipe_from_file = ft_uint_to_char(arg->next->str);//

				arg->ignore_me = TRUE;
				arg->next->ignore_me = TRUE;
			}


			// on note les |
			if ('|' == *arg->str && arg->next && '|' != *arg->next->str)
			{
				arg = deltoken(&arg);
				if (lastarg == NULL)
				{
					instruct->program_args = NULL;
				}
				else
				{
					lastarg->next = NULL;
				}
				tmpinstruct = instruct->next;
				instruct->pipe_to_instruct = ft_memalloc(sizeof(*(instruct->pipe_to_instruct)));
				instruct->pipe_to_instruct->pipe_to_fd = dup(1);
				instruct->pipe_to_instruct->program_name = ft_uintdup(arg->str);
				if (arg->next && '|' != *arg->next->str)
					instruct->pipe_to_instruct->program_args = arg->next;
				/*ft_printf("\n\n\n");
				ft_uintput(instruct->pipe_to_instruct->program_name);
				ft_printf("\n\n\n");*/
				instruct = instruct->pipe_to_instruct;
				instruct->next = tmpinstruct;
				arg = deltoken(&arg);
				continue;
			}
			
			
			// on note les  >&- et les aggrégations de descripteurs de fichiers
			lastarg = arg;
			if (arg)
				arg = arg->next;
		}
		instruct = instruct->next;
	}
	return (first_instruct);
}

void		ft_execwait(char *path, char **av)
{
	pid_t	father;
	int		osef;
	char	**pcur;

	osef = 0;
	father = fork();
	if (father > 0)
		wait(&osef);
	else
	{

		pcur = ft_getpcur();
		execve(path, av, pcur);
		ft_strsplit_del(&pcur);
	}
}

char 			**instruct_to_agrv(t_instruct *instruct, int *argc)
{
	t_token	*arg;
	int	size;
	char 	**argv;
	size_t i = 0;

	arg = instruct->program_args;
	size = 0;
	while(arg)
	{
		if (!arg->ignore_me)
			size++;
		arg = arg->next;
	}
	*argc = size + 2;
	arg = instruct->program_args;
	//ft_printf("--->%i<---", (int)size);
	argv = (char **)ft_memalloc(sizeof(char*) * (size + 2));
	argv[i++] = ft_uint_to_char(instruct->program_name);
	while(arg)
	{
		if (!arg->ignore_me)
			argv[i++] = ft_uint_to_char(arg->str);
		arg = arg->next;
	}
	return argv;
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
extern char **environ;


t_bool		execbuiltin(char **argv)
{
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


void		instruct_file2fd(t_instruct *instruct)
{
	int val;

	val = O_WRONLY | O_CREAT;
	if (instruct->pipe_from_file)
	{
		instruct->pipe_from_fd = open(instruct->pipe_from_file, O_RDONLY);
	}
	if (instruct->replace_file)
	{
		val = val | O_TRUNC;
	}
	else 
	{
		val = val | O_APPEND;
	}

	if (ft_strequ(instruct->pipe_to_file, "&1"))
	{
		ft_strdel(&(instruct->pipe_to_file));
		instruct->pipe_to_file = NULL;
		instruct->pipe_to_fd = dup(1);
	}
	else if (ft_strequ(instruct->pipe_to_file, "&-"))
	{
		instruct->pipe_to_fd = open("/dev/null", O_WRONLY);
	}
	else if (instruct->pipe_to_file)
	{
		instruct->pipe_to_fd = open(instruct->pipe_to_file, val, 0755);	
	}

}

void		instruct_file2fd_chain(t_instruct *instruct)
{
	while (instruct)
	{
		instruct_file2fd(instruct);
		instruct = instruct->pipe_to_instruct;
	}	
}

void	del_argv(char **argv, int argc)
{
	int i = 0;

	while (i < argc)
	{
		ft_memdel((void**)&(argv[i]));
		i++;
	}
	free((void**)argv);
}

void exec_instrut_simple(t_instruct *instruct)
{
	char 		*tmp;
	char	*whereis;
	t_bool	isbuildin;
	char 			**argv;
	int argc;

	tmp = ft_uint_to_char(instruct->program_name);
	whereis = ft_whereis(tmp);
	ft_memdel((void**)&tmp);
	argc = 0;
	argv = instruct_to_agrv(instruct, &argc);
	isbuildin = execbuiltin(argv);
	if (!isbuildin && !whereis)
	{
		ft_strdel(&whereis);
		ft_putstr_error("Command no found.\n");
		del_argv(argv, argc);
		return ;
	}
	if (!isbuildin)
		ft_execwait(whereis, argv);
	ft_strdel(&whereis); 
	del_argv(argv, argc);
}

t_instruct *instructs_pipe_chain(t_instruct *instruct, int savefd0, int savefd1, int savefd2, int fd)
{
	int 	p[2];

	if (instruct->pipe_to_instruct)
	{
		if (-1 == fd)
		{
			pipe(p);
			dup2(instruct->pipe_from_fd, 0);
			if (instruct->aggregate_fd)
			{
				dup2(p[1], 2);
			}
		    dup2(p[1], 1);
			exec_instrut_simple(instruct);
			close(p[1]);
			dup2(savefd2, 2);
			close(instruct->pipe_from_fd);
			return instructs_pipe_chain(instruct->pipe_to_instruct, savefd0, savefd1, savefd2, p[0]);
		}
		else
		{
			dup2(fd, 0);
		    pipe(p);
		    dup2(p[1], 1);
		    if (instruct->aggregate_fd)
			{
				dup2(p[1], 2);
			}
			exec_instrut_simple(instruct);
		    close(p[1]);
		    dup2(savefd2, 2);

			return instructs_pipe_chain(instruct->pipe_to_instruct, savefd0, savefd1, savefd2, p[0]);	
		}
	}
	else
	{
		//exit(0);
		dup2(fd, 0);
		dup2(instruct->pipe_to_fd, 1);
		if (instruct->aggregate_fd)
		{
			dup2(instruct->pipe_to_fd, 2);
		}

		exec_instrut_simple(instruct);
		dup2(savefd0, 0);
		dup2(savefd1, 1);
		dup2(savefd2, 2);
		
		//exit(0);
		return instruct->next;
	}
}

t_instruct	*instruct_pipe_fd(t_instruct *instruct)
{
	int savefd2;
	int savefd1;
	int savefd0;


	savefd0 = dup(0);
	savefd1 = dup(1);
	savefd2 = dup(2);
	if (instruct->aggregate_fd)
	{
		dup2(instruct->pipe_to_fd, 2);
	}
	dup2(instruct->pipe_to_fd, 1);
	dup2(instruct->pipe_from_fd, 0);
	exec_instrut_simple(instruct);
	close(instruct->pipe_to_fd);
	close(instruct->pipe_from_fd);
	
	dup2(savefd0, 0);
	dup2(savefd1, 1);
	dup2(savefd2, 2);
	return instruct->next;
}

void ft_erase(t_instruct **instruct)
{
	ft_bzero(*instruct, sizeof(t_instruct));
	
}

void	delinstructs(t_instruct *instruct)
{
	static t_list *list = NULL;

	if (!list)
	{
		list = ft_lstnew(&instruct, sizeof(t_instruct*));
	}
	else
	{
		ft_lstadd(&list, ft_lstnew(&instruct, sizeof(t_instruct*)));
	}
}

void	execute(t_command *command)
{
	t_instruct	*instruct = command2instruct(command);
	t_instruct 	*first;
	
	
	

	first = instruct;
	while(instruct)
	{
		if (instruct->pipe_to_instruct)
		{
			instruct_file2fd_chain(instruct);
			instruct = instructs_pipe_chain(instruct, dup(0), dup(1), dup(2), -1);
		}
		else
		{
			if (instruct->pipe_from_file || instruct->pipe_to_file)
			{
				instruct_file2fd_chain(instruct);
				instruct = instruct_pipe_fd(instruct);
			}
			else if (instruct->pipe_from_fd)
			{
				instruct = instruct_pipe_fd(instruct);
			}
			else
			{
				exec_instrut_simple(instruct);
				instruct = instruct->next;	
			}
		}
	}

	delinstructs(first);
	
}