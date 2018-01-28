#include "main.h"

void cc_clear(t_command *command)
{
	command->cc_pos_start = 0;
	command->cc_pos_stop = 0;
	command->cc_mode_enabled = 0;
}

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

void ft_uintputchar(unsigned int *str)
{
	unsigned char *s;

	s = str;
	if (s[0] > 0)
		ft_putchar(s[0]);
	if (s[1] > 0)
		ft_putchar(s[1]);
	if (s[2] > 0)
		ft_putchar(s[2]);
	if (s[3] > 0)
		ft_putchar(s[3]);
}

void	ft_uintput(unsigned int *str)
{
	size_t y;
	unsigned char *s;

	if (NULL == str || NULL == *str)
		return ;
	s = str;
	y = 0;
	while(str[y])
	{
		ft_uintputchar(str + y);
		y++;
	}
}

unsigned int	*ft_uintdup(unsigned int *s1)
{
	unsigned int	*s2;
	size_t		len;

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

char *ft_uint_to_char(unsigned int *input)
{
	unsigned char *s;
	size_t			i;
	size_t			i_output;
	char *o;

	o = ft_strnew(ft_uintlen(input) * 4);
	i = 0;
	i_output = 0;
	while (input[i])
	{
		s = input + i;
		if (s[0] > 0)
			o[i_output++] = s[0];
		if (s[1] > 0)
			o[i_output++] = s[1];
		if (s[2] > 0)
			o[i_output++] = s[2];
		if (s[3] > 0)
			o[i_output++] = s[3];
		i++;
	}
	return (o);
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

struct termios attrib_old;

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

void			t_save()
{
	tcgetattr( 0, &attrib_old);
}

void			t_restore()
{
	tcsetattr(0, TCSANOW, &attrib_old);
}

t_bool t_enable_insert_mode()
{
	char *str = tgetstr("im", NULL);

	if (!str)
		return (FALSE);
	tputs(str, ft_strlen(str), ft_putchar);
	return (TRUE);
	//ft_strdel(&str);	 TODO FREE
}

t_bool t_disable_insert_mode()
{
	char *str = tgetstr("ei", NULL);
	if (!str)
		return (FALSE);
	tputs(str, ft_strlen(str), ft_putchar);
	return (TRUE);
	// TODO FREE ?
}

t_bool t_move_left()
{
	char *str = tgetstr("le", NULL);

	if (!str)
	{
		ft_printf("\nBINGO !\n");
		return (FALSE);
	}
	tputs(str, ft_strlen(str), ft_putchar);
	return (TRUE);
	// TODO FREE ?
}

t_bool t_move_right()
{
	char *str = tgetstr("nd", NULL);

	if (!str)
		return (FALSE);
	tputs(str, ft_strlen(str), ft_putchar);
	return (TRUE);
	// TODO FREE ?
}

t_bool t_delete_last_char()
{
	char *str = tgetstr("dc", NULL);

		if (!str)
	{
		ft_printf("\nBINGO2 !\n");
		return (FALSE);
	}
	if (!str)
		return (FALSE);
	t_move_left();
	tputs(str, ft_strlen(str), ft_putchar);
	return (TRUE);
	//  TODO FREE ?
}

t_bool t_delete_after_cursor()
{
	char *str = tgetstr("cd", NULL);

	if (!str)
		return (FALSE);
	//t_move_left();
	tputs(str, ft_strlen(str), ft_putchar);
	return (TRUE);
}

t_bool t_start_under()
{
	char *str = tgetstr("so", NULL);

	if (!str)
		return (FALSE);
	//t_move_left();
	tputs(str, ft_strlen(str), ft_putchar);
	return (TRUE);
}

t_bool t_stop_under()
{
	char *str = tgetstr("se", NULL);

	if (!str)
		return (FALSE);
	//t_move_left();
	tputs(str, ft_strlen(str), ft_putchar);
	return (TRUE);
}


t_bool display_input_left(unsigned int buff, t_command *command)
{
	if (4479771 == buff)
	{
		if (command->pos == 0)
			return (TRUE);
		if (command->pos > 0)
			command->pos--;
		/*if (command->cc_mode_enabled)
		{
			t_move_left();
			t_disable_insert_mode();
			t_start_under();
			ft_uintputchar(command->str + command->pos);
			t_stop_under();
			t_enable_insert_mode();
			
		}*/ // BONUS un peu raté
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
		if (t_move_right())
			command->pos++;
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
	t_move_left();
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
	t_move_left();
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
	t_delete_after_cursor();
	ft_insert_char(&(command->str), buff, command->pos);
	ft_uintput(command->str + command->pos);
	command->pos = ft_uintlen(command->str);
	savepos++;
	while (savepos < command->pos)
	{
		display_input_left(4479771, command);
	}
	return (TRUE);
}

void	execute(t_command *command);

t_bool display_input_validate(unsigned int buff, t_command **command)
{
	t_command		*new_command;

	if ('\n' == buff)
	{
		ft_putchar('\n');
		/*
		ft_printf("\nExecuter ");
		ft_uintput(((t_command *)(*command))->str);
		ft_printf("\n");*/
		execute(*command);
		ft_putstr("$> ");
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
		if (NULL == goto_historic->str)
			return (TRUE);
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

t_bool display_input_copypast(unsigned int buff, t_command *command, unsigned int **clipboard)
{
	// 7011 copier
	// 7024 past
	// 6979 cut
	// 7027 select
	size_t min;
	size_t max;
	size_t	i;

	i = 0;
	if (7027 == buff) // select
	{
		//ft_printf("select\n");
		command->cc_pos_start = command->pos;
		command->cc_mode_enabled = TRUE;
		//t_start_under();
		//ft_printf("mode : %d\npos1 : %d\npos2 : %d\n", command->cc_mode_enabled, command->cc_pos_start, command->cc_pos_stop);
		return (TRUE);
	}
	if (7024 == buff) // past
	{
		//ft_printf("mode : %d\npos1 : %d\npos2 : %d\n", command->cc_mode_enabled, command->cc_pos_start, command->cc_pos_stop);
		if (NULL != *clipboard)
		{
			while ((*clipboard)[i])
			{
				display_input_insert((*clipboard)[i], command);
				i++;
			}
		}
		return (TRUE);
	}
	if (command->cc_mode_enabled && 7011 == buff) // copy
	{
		//ft_printf("copy\n");
		command->cc_pos_stop = command->pos;
		command->cc_mode_enabled = FALSE;
		ft_strdel(clipboard);
		
		min = (command->cc_pos_start < command->cc_pos_stop) ? command->cc_pos_start : command->cc_pos_stop;
		max = (command->cc_pos_start < command->cc_pos_stop) ? command->cc_pos_stop : command->cc_pos_start;
		*clipboard = ft_memalloc((max - min + 1) * 4);
		ft_memcpy(*clipboard, command->str + min, (max - min) * 4);

		//t_stop_under();
		//ft_printf("mode : %d\npos1 : %d\npos2 : %d\n", command->cc_mode_enabled, command->cc_pos_start, command->cc_pos_stop);
		return (TRUE);
	}
	if (command->cc_mode_enabled && 6979 == buff) // cut
	{
		command->cc_pos_stop = command->pos;
		command->cc_mode_enabled = FALSE;
		ft_strdel(clipboard);
		
		min = (command->cc_pos_start < command->cc_pos_stop) ? command->cc_pos_start : command->cc_pos_stop;
		max = (command->cc_pos_start < command->cc_pos_stop) ? command->cc_pos_stop : command->cc_pos_start;
		*clipboard = ft_memalloc((max - min + 1) * 4);
		ft_memcpy(*clipboard, command->str + min, (max - min) * 4);
		
		if (command->pos == min)
		{
			while (command->pos != max)
				display_input_right(4414235, command);
		}
		while (command->pos != min)
			display_input_ondelete(127, command);
		return (TRUE);
	}
	////ft_printf("%d\n", (int)buff);
	//ft_printf("mode : %d\npos1 : %d\npos2 : %d\n", command->cc_mode_enabled, command->cc_pos_start, command->cc_pos_stop);
	return (FALSE);
}

void complete_buff(unsigned int *buff)
{
	int toadd;
	int toaddsave;
	int newbuff;

	newbuff = 0;
	toadd = 0;
	if (*buff == 27) // échap
	{
		read(STDIN_FILENO, &newbuff, 1);
		if (91 == newbuff)
		{
			read(STDIN_FILENO, &newbuff, 1);
			if (65 == newbuff) // haut
				*buff = 4283163;
			if (66 == newbuff) // bas
				*buff = 4348699;
			if (67 == newbuff) // droite
				*buff = 4414235;
			if (68 == newbuff) // gauche
				*buff = 4479771;
		}
		else if ('c' == newbuff || 'p' == newbuff || 'C' == newbuff || 's' == newbuff) // copy, paste, cut
		{
			*buff = *buff << 8;
			*buff = *buff | newbuff;
		}
		return ;
	}
	if (*buff <= 127)
		return;
	if (*buff <= 223) // 1 octet en plus à lire
		toadd = 1;
	else if (*buff < 240) // 2 octets en plus à lire
		toadd = 2;
	else // 3 octets en plus à lire
		toadd = 3;
	toaddsave = toadd;
	//*buff = *buff << 8;
	read(STDIN_FILENO, &newbuff, toaddsave);
	newbuff = newbuff << 8;
	*buff = newbuff | *buff; 
}


char 	*display_input_heredoc(char *stop)
{
	char *line;
	char *input;

	line = NULL;
	input = NULL;
	t_restore();
	ft_putstr("heredoc> ");
	while (42)
	{
		ft_gnl(STDIN_FILENO, &line);
		if (ft_strlen(line)) // todo control ctrl d
		{
			if (ft_strequ(line, stop))
			{
				ft_memdel(&line);
				t_init();

				return (!input ? ft_strdup("") : input);
			}
			if (!input)
			{
				input = ft_strdup(line);
				input = ft_strjoin_multi(TRUE, input, ft_strdup("\n"), NULL);
			}
			else
				input = ft_strjoin_multi(TRUE, input, line, ft_strdup("\n"), NULL);
			ft_putstr("heredoc> ");
		}
		else
			ft_memdel(&line);
	}
}

void display_input(t_command **command)
{
	unsigned int buff;
	unsigned int *clipboard;
	int test;

	buff = 0;
	clipboard = NULL;
	ft_putstr("$> ");
	while (1) {
		if (test = read(STDIN_FILENO, &buff, 1) > 0)
		{
			complete_buff(&buff);
			//ft_printf("%b\n", buff);
			if (27 == buff)
			{
				ft_printf("ah ?");
				cc_clear(*command);
				continue ;
			}
			//ft_printf("\n%b - %d\n", buff, buff);
			if (display_input_ondelete(buff, *command)) {cc_clear(*command);}
			else if (display_input_validate(buff, command)) {cc_clear(*command);}
			else if (display_input_left(buff, *command)) {}
			else if (display_input_right(buff, *command)) {}
			else if (display_input_historic(buff, *command)) {cc_clear(*command);}
			else if (display_input_copypast(buff, *command, &clipboard)) {}
			//
			else if (display_input_insert(buff, *command)) {cc_clear(*command);}

		}
		else
		{
			ft_printf("dsl mec");
			exit(0);
		}
		buff = 0;
	}
}


unsigned int *              shell_input()
{
	t_command		*command;

	command = ft_memalloc(sizeof(t_command));
	t_save();
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