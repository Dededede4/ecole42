#include "main.h"
#include<signal.h>

void cc_clear(t_command *command)
{
	command->cc_pos_start = 0;
	command->cc_pos_stop = 0;
	command->cc_mode_enabled = 0;
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
		else if(27 == newbuff)
		{
			read(STDIN_FILENO, &newbuff, 1);
			if (91 == newbuff)
			{
				read(STDIN_FILENO, &newbuff, 1);
				if (65 == newbuff) // haut
					*buff = 1096489755;
				if (66 == newbuff) // bas
					*buff = 1113266971;
				if (67 == newbuff) // droite
					*buff = 1130044187;
				if (68 == newbuff) // gauche
					*buff = 1146821403;
			}
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


void sig_handler(int signo)
{
    if (signo == SIGINT)
    {
        //printf("received SIGINT\n");
    }
    if (signo == SIGQUIT)
    {
    	// printf("received SIGQUIT\n");
    }
    /*else if (signo == SIGKILL)
        printf("received SIGKILL\n");
    else if (signo == SIGSTOP)
        printf("received SIGSTOP\n");*/
}


void enable_signals()
{
	signal(SIGINT, sig_handler);
	//signal(SIGQUIT, sig_handler);
}





void display_input(t_command **command)
{
	unsigned int buff;
	unsigned int *clipboard;

	buff = 0;
	clipboard = NULL;
	ft_putstr("$> ");
	while (read(STDIN_FILENO, &buff, 1) > 0) {
		if ('\t' == buff)
		{
			buff = 0;
			continue;
		}
		if (4 == buff)
			return ;
		complete_buff(&buff);
		if (27 == buff)
		{
			ft_printf("ah ?");
			cc_clear(*command);
			continue ;
		}

		//ft_printf("\n%b - %d\n", buff, buff);
		if (display_input_ondelete(buff, *command)) {cc_clear(*command);}
		else if (display_input_validate(buff, command)) {cc_clear(*command);}
		else if (display_input_supermoves(buff, *command)){}
		else if (display_input_left(buff, *command)) {}
		else if (display_input_right(buff, *command)) {}

		else if (display_input_historic(buff, *command)) {cc_clear(*command);}
		else if (display_input_copypast(buff, *command, &clipboard)) {}
		//
		else if (display_input_insert(buff, *command)) {cc_clear(*command);}
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
	enable_signals();
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