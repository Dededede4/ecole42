#include "main.h"

void ft_uintput(unsigned int *str);
unsigned int	*ft_uintdup(unsigned int *s1);
unsigned int	*ft_uintnew(size_t size);
char *ft_uint_to_char(unsigned int *input);

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
	ft_printf("\nla->");
	ft_uintput(s);
	d = 0;
	while (s[d] == ' ' || s[d] == '\t' || s[d] == '\n')
		d++;
	if (s[d] == '\0')
		return (ft_uintnew(0));
	f = ft_uintlen(s) - 1;
	while (s[f] == ' ' || s[f] == '\t' || s[f] == '\n')
		f--;
	ft_printf("\nla2->");
	ft_uintput(s);
	return (ft_uintsub(s, d, f - d + 1));
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
			else if (str[i] == quote) // fin
			{
				quote = '\0';
			}
			else
			{
				// au milieu
			}
		}
		else if ('\t' == str[i] || ' ' == str[i])
		{
			if (!quote)
			{
					return i;
			}
		}
		else if ('\t' == str[i + 1] || ' ' == str[i + 1] || ';' == str[i + 1] || '>' == str[i + 1] ||  '<' == str[i + 1] || '|' == str[i + 1])
		{
			if (!quote)
			{
					return i;
			}
		}
		else if (';' == str[i] || '>' == str[i] || '<' == str[i] || '|' == str[i])
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
	return str;

}

t_token		*tokenize(unsigned int *str) // todo char **;
{
	// il faudra copier-coller ça afin de compter tout ce qu'on veut
	size_t			i;
	size_t			stop;
	t_token			*token;
	t_token			*first_token;
	size_t			len;


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
			stop = get_word_pos(str, i) + 1;
			
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
			token->str = ft_memdup(str + i, (stop - i) * 4);
			token->str = clear_escapes(token->str);
			i = stop;
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

char *heredoc(unsigned int *stop)
{
	char *input;
	char *global;
	char *tmp;

	global = NULL;
	ft_putstr("> ");
	input = NULL;
	while(ft_gnl(STDIN_FILENO, &input))
	{
		ft_printf("what?");
		tmp = ft_uint_to_char(stop);
		if (0 == ft_strcmp(tmp, input))
			return (global);
		global = ft_strjoin_multi(TRUE, global, input);
	}
	ft_printf("fin");
	return (global);
}


t_instruct *command2instruct(t_command *command)
{
	size_t	i;
	size_t end;
	t_instruct	*instruct;
	t_instruct	*first_instruct;
	t_token		*token;
	t_token		*arg;
	char 		*tmp;

	arg = NULL;
	token = tokenize(command->str);
	if (!token)
		return NULL; // ?
	instruct = ft_memalloc(sizeof(*instruct));
	instruct->program_name = token->str;
	first_instruct = instruct;

	token = token->next;
	while(token)
	{
		if (0 == ft_uintcmp(token->str, L";"))
		{
			if (token->next)
			{
				arg = NULL;
				token = token->next;
				instruct->next = ft_memalloc(sizeof(*instruct));
				instruct = instruct->next;
				instruct->program_name = ft_uintdup(token->str);
			}
			else
				return first_instruct;
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
				arg->next = ft_memalloc(sizeof(*arg));;
				arg = arg->next;
			}
			arg->str = ft_uintdup(token->str);
		}
		token = token->next;
	}

	// Maintenant on va convertir les redirections

	instruct = first_instruct;
	while(instruct)
	{
		arg = instruct->program_args;
		while (arg && arg->next)
		{
			// TODO obtenir les FD et juste donner des FD

			// On va noter les >>
			if ('>' == *arg->str && '>' == *arg->next->str)
			{
				if (!arg->next->next){} // TODO error
				instruct->pipe_to_file = arg->next->next->str;
				instruct->replace_file = FALSE;
			}
			
			// On note les <<
			ft_putstr("-->");
			ft_uintput(arg->str);
			ft_putstr("<-->");
			ft_uintput(arg->next->str);
			ft_putstr("<--");
			if ('<' == *arg->str && '<' == *arg->next->str)
			{
				ft_printf("go\n");
				if (arg->next->next)
					ft_putstr(heredoc(arg->next->next->str));
				else
					ft_putstr(heredoc(L"<<"));
				// TODO il faut une fonction de type ft_uinttoi
				/*if (!arg->next->next){} // TODO error
				instruct->pipe_form_fd = arg->next->next->str;*/
			}
			

			// on note les >
			if ('>' == *arg->str && '>' != *arg->next->str)
			{
				if (!arg->next->next){} // TODO error
				instruct->pipe_to_file = arg->next->next->str;
				instruct->replace_file = TRUE;
			}

			// on note les <
			if ('<' == *arg->str && '<' != *arg->next->str)
			{
				if (!arg->next->next){} // TODO error
				tmp = ft_uint_to_char(arg->next->str);
				instruct->pipe_from_fd = open(tmp, O_RDONLY);
			}


			// on note les |
			// on note les  >&- et les aggrégations de descripteurs de fichiers
			
			arg = arg->next;
		}
		instruct = instruct->next;
	}
	return (first_instruct);
}

void		ft_execwait_std(char *path, char **av, int stdin/*, int stdout*/)
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
		if (dup2(stdin, STDIN_FILENO) == -1) {
          perror("dup2");
          return;
        }
        close(stdin);
		pcur = ft_getpcur();
		execve(path, av, pcur);
		ft_strsplit_del(&pcur);
	}
}

char 			**instruct_to_agrv(t_instruct *instruct)
{
	t_token	*arg;
	size_t	size;
	char 	**argv;
	size_t i = 0;

	arg = instruct->program_args;
	size = 0;
	while(arg)
	{
		size++;
		arg = arg->next;
	}
	arg = instruct->program_args;
	//ft_printf("--->%i<---", (int)size);
	argv = (char **)ft_memalloc(sizeof(char*) * (size + 2));
	argv[i++] = ft_uint_to_char(instruct->program_name);
	while(arg)
	{
		argv[i++] = ft_uint_to_char(arg->str);
		arg = arg->next;
	}
	return argv;
}

void	execute(t_command *command)
{
	t_instruct	*instruct = command2instruct(command);
	t_token		*token;
	char 		*tmp;
	while(instruct)
	{
		//ft_printf("\nIl faut executer ");
		tmp = ft_uint_to_char(instruct->program_name);

		ft_execwait_std(tmp, instruct_to_agrv(instruct), instruct->pipe_from_fd);
		
		//ft_uintput(instruct->program_name);
		//ft_printf("et le printer vers le fd %i", instruct->pipe_from_fd);
		//ft_putstr("\n");
		instruct = instruct->next;
	}
	ft_printf("fin");
}