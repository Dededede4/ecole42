#include "main.h"

size_t	ft_uintlen(unsigned int *s)
{
	size_t	i;

	if (NULL == s || NULL == *s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_uintput(unsigned int *str)
{
	size_t i;
	unsigned char *s;

	if (NULL == str || NULL == *str)
		return ;
	s = str;
	i = 0;
	while(s[i])
	{
		if (s[i] > 0)
			ft_putchar(s[i]);
		if (s[i + 1] > 0)
		{
			ft_putchar(s[i + 1]);
		}
		if (s[i + 2] > 0)
			ft_putchar(s[i + 2]);
		if (s[i + 3] > 0)
		{
			ft_putchar(s[i + 3]);
		}
		i += 4;
	}
}

unsigned int	*ft_uintdup(unsigned int *s1)
{
	unsigned int	*s2;
	int		len;

	len = ft_uintlen(s1) + 1;
	s2 = ft_memalloc((sizeof(*s2) * len));
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, sizeof(*s2) * len);
	return (s2);
}

void	ft_uintdel(unsigned int **as)
{
	ft_memdel((void *)as);
}

unsigned int	*ft_uintnew(size_t size)
{
	return (ft_memalloc((size + 1) * 4));
}

unsigned int	*ft_uintjoin(unsigned int const *s1, unsigned int const *s2)
{
	size_t	len1;
	size_t	len2;
	unsigned int	*new;

	if (s1 && !s2)
		return (ft_uintdup(s1));
	if (!s1 && s2)
		return (ft_uintdup(s2));
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_uintlen(s1);
	len2 = ft_uintlen(s2);
	new = ft_uintnew(len1 + len2);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, (void*)(s1), len1 * 4);
	ft_memcpy(new + len1, (void*)(s2), len2 * 4);
	return (new);
}

unsigned int	*ft_uintjoin_multi(t_bool autofree, ...)
{
	va_list			ap;
	unsigned int	*str;
	unsigned int	*strfree_arg;
	unsigned int	*strfree;

	va_start(ap, autofree);
	str = NULL;
	while ((strfree_arg = va_arg(ap, unsigned int *)))
	{
		strfree = str;
		str = ft_uintjoin(str, strfree_arg);
		free(strfree);
		if (autofree)
			free(strfree_arg);
	}
	va_end(ap);
	return (str);
}





unsigned int		*ft_uintdup_len(unsigned int *str, size_t len)
{
	unsigned int	*newstr;

	newstr = ft_uintnew(len);
	ft_memcpy(newstr, str, len * 4);
	return (newstr);
}


void	ft_insert_char(unsigned int **str, unsigned int c, size_t pos)
{
	unsigned int *begin;
	unsigned int *end;
	unsigned int *middle;

	middle = ft_memalloc(8);
	middle[0] = c;
	if (NULL == *str)
	{
		*str = middle;
		return;
	}
	if ('\0' == ((unsigned int *)(*str))[pos])
	{
		begin = ft_uintdup(*str);
		ft_uintdel(str);
		*str = ft_uintjoin_multi(TRUE, begin, middle, NULL);
		return;
	}

	begin = ft_uintdup_len((*str), pos);
	end = ft_uintdup((unsigned int*)(*str) + pos);
	ft_uintdel(str);
	*str = ft_uintjoin_multi(TRUE, begin, middle, end, NULL);
}

void	ft_delete_char(unsigned int **str, size_t pos)
{
	unsigned int *begin;
	unsigned int *end;
	size_t len;

	if (NULL == *str)
		return ;
	len = ft_uintlen(*str);
	//ft_printf("\n'%s' pos%d len%d\n", *str, (int)pos, (int)len);
	if (len < pos || 0 == len)
		return ;
	begin = ft_uintdup_len((*str), pos);
	if (len - 1 == pos)
	{
		ft_uintdel(str);
		*str = begin;
		return;
	}
	//ft_printf("\n'%s' pos%d len%d\n", *str, (int)pos, (int)len);
	end = ft_uintdup((unsigned int*)(*str) + pos + 1);
	*str = ft_uintjoin_multi(TRUE, begin, end, NULL);
}
// TODO être sûr de bien tout comprendre
// TODO j'ai toujours pas la lib un ft_exet ???
void			t_init()
{
	char           *name_term;
	struct termios term;

	if ((name_term = ft_getenv("TERM")) == NULL)
		exit(0);
	if (tgetent(NULL, name_term) == ERR)
		exit(0);
	if (tcgetattr(0, &term) == -1)
		exit(0);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		exit(0);
}

void t_enable_insert_mode()
{
	char *str = tgetstr("im", NULL);

	tputs(str, ft_strlen(str), ft_putchar);
	//ft_strdel(&str);	 TODO FREE
}

void t_disable_insert_mode()
{
	char *str = tgetstr("ei", NULL);

	tputs(str, ft_strlen(str), ft_putchar);
	// TODO FREE ?
}

void t_move_left()
{
	char *str = tgetstr("le", NULL);

	tputs(str, ft_strlen(str), ft_putchar);
	// TODO FREE ?
}

void t_move_right()
{
	char *str = tgetstr("nd", NULL);

	tputs(str, ft_strlen(str), ft_putchar);
	// TODO FREE ?
}

void t_delete_last_char()
{
	char *str = tgetstr("dc", NULL);

	t_move_left();
	tputs(str, ft_strlen(str), ft_putchar);
	//  TODO FREE ?
}

void t_delete_after_cursor()
{
	char *str = tgetstr("cd", NULL);

	t_move_left();
	tputs(str, ft_strlen(str), ft_putchar);
}

t_bool display_input_left(unsigned int buff, t_command *command)
{
	if (4479771 == buff)
	{
		if (command->pos == 0)
			return (TRUE);
		if (command->pos > 0)
			command->pos--;
		t_move_left();
		return (TRUE);
	}
	return (FALSE);
}

t_bool display_input_right(unsigned int buff, t_command *command)
{
	if (4414235 == buff)
	{
		if (command->pos == ft_uintlen(command->str))
			return (TRUE);
		// TOTO checker comportement à la fin de la ligne 
		command->pos++;
		t_move_right();
		return (TRUE);
	}
	return (FALSE);
}

void clear_input(t_command *command)
{
	if (command->str == NULL)
		return;
	while (command->pos != 0)
	{
		display_input_left(4479771, command);
	}
	t_delete_after_cursor();
	ft_memdel(&(command->str));
}

void clear_input_soft(t_command *command)
{
	if (command->str == NULL)
		return;
	while (command->pos != 0)
	{
		display_input_left(4479771, command);
	}
	t_delete_after_cursor();
}

void show_command(t_command *command)
{
	if (command->str == NULL)
		return;
	ft_uintput(command->str);
	command->pos = ft_uintlen(command->str);
}

t_bool display_input_ondelete(unsigned int buff, t_command *command)
{
	size_t savepos;

	if (buff == 127)
	{
		if (command->pos > 0)
			command->pos--;
		else
			return (TRUE);
		savepos = command->pos;
		clear_input_soft(command);
		ft_delete_char(&(command->str), savepos);
		show_command(command);
		while (savepos < command->pos)
		{
			display_input_left(4479771, command);
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool display_input_insert(unsigned int buff, t_command *command)
{
	int i;
	unsigned char *b;
	size_t savepos;

	b = &buff;
	i = 0;
	savepos = command->pos;
	clear_input_soft(command);
	ft_insert_char(&(command->str), buff, savepos);
	savepos++;
	show_command(command);
	while (savepos < command->pos)
	{
		display_input_left(4479771, command);
	}
	return (TRUE);
}

t_bool display_input_validate(unsigned int buff, t_command **command)
{
	t_command		*new_command;

	if ('\n' == buff)
	{
		ft_printf("\nExecuter ");
		ft_uintput(((t_command *)(*command))->str);
		ft_printf("\n");
		if(NULL == ((t_command *)(*command))->str || '\0' == ((t_command *)(*command))->str[0])
			return (TRUE);
		(*command)->pos = ft_uintlen((*command)->str);
		new_command =  ft_memalloc(sizeof(t_command));
		new_command->prev = (*command);
		new_command->prev->next = new_command;
		*command = new_command;
		return (TRUE);
	}
	return (FALSE);
}

t_bool display_input_historic(unsigned int buff, t_command *command)
{
	// 4414235 = flèche droite
	// 4283163 = flèche haut
	// 4348699 = flèche bas
	// 4 = ctrl d
	t_command *goto_historic;

	if (4283163 == buff)
	{
		/*if (0 != command->pos || 0 != ft_uintlen(command->str))
			return (TRUE);*/
		if (command->historic_pos)
			goto_historic = command->historic_pos->prev;
		else
			goto_historic = command->prev;
		if (!goto_historic)
			return (TRUE);
		clear_input(command);
		command->historic_pos = goto_historic;
		command->pos = 0;
		while(goto_historic->str[command->pos])
		{
			display_input_insert(goto_historic->str[command->pos], command);
		}
		// On efface c
		// On avance le curseur jusqu'à la fin du message
		// on effece chaque caractère un par un
		/*ft_uintput(((t_command *)(*command))->str);
		ft_printf("\n");
		if(NULL == ((t_command *)(*command))->str || '\0' == ((t_command *)(*command))->str[0])
			return (TRUE);
		(*command)->pos = ft_uintlen((*command)->str);
		new_command =  ft_memalloc(sizeof(t_command));
		new_command->perv = (*command);
		*command = new_command;*/
		return (TRUE);
	}
	if (4348699 == buff)
	{
		clear_input(command);
		if (NULL == command->historic_pos || NULL == command->historic_pos->next)
			return (TRUE);
		goto_historic = command->historic_pos->next;
		command->historic_pos = goto_historic;
		command->pos = 0;
		while(goto_historic->str[command->pos]) // Pour copier le texte à partir de la position actuelle
		{
			display_input_insert(goto_historic->str[command->pos], command);
		}
		return (TRUE);
	}
	return (FALSE);
}

void display_input(t_command **command)
{
	unsigned int buff;

	buff = 0;
	while (1) {
		if (read(STDIN_FILENO, &buff, 4) > 0)
		{
			if (display_input_ondelete(buff, *command)) {}
			else if (display_input_validate(buff, command)) {}
			else if (display_input_left(buff, *command)) {}
			else if (display_input_right(buff, *command)) {}
			else if (display_input_historic(buff, *command)) {}
			//
			else if (display_input_insert(buff, *command)) {}
		}
		buff = 0;
	}
}

unsigned int *              shell_input()
{
	t_command		*command;

	command = ft_memalloc(sizeof(t_command));
	t_init();
	t_enable_insert_mode();
	display_input(&command);
	return ft_uintnew(0);
}

int              main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	ft_loadenv(environ);
	shell_input();
	return (0);
}