#include "main.h"

void	ft_insert_char(char **str, char c, size_t pos)
{
	char *begin;
	char *end;
	char *middle;

	middle = ft_strnew(1);
	middle[0] = c;
	if (NULL == *str)
	{
		*str = middle;
		return;
	}
	if ('\0' == (*str)[pos])
	{
		begin = ft_strdup(*str);
		ft_strdel(str);
		*str = ft_strjoin_multi(TRUE, begin, middle, NULL);
		return;
	}

	begin = ft_strdup_len((*str), pos);
	end = ft_strdup((*str) + pos);
	ft_strdel(str);
	*str = ft_strjoin_multi(TRUE, begin, middle, end, NULL);
}

void	ft_delete_char(char **str, size_t pos)
{
	char *begin;
	char *end;
	size_t len;

	if (NULL == *str)
		return ;
	len = ft_strlen(*str);
	//ft_printf("\n'%s' pos%d len%d\n", *str, (int)pos, (int)len);
	if (len < pos || 0 == len)
		return ;
	begin = ft_strdup_len((*str), pos);
	if (len - 1 == pos)
	{
		ft_strdel(str);
		*str = begin;
		return;
	}
	//ft_printf("\n'%s' pos%d len%d\n", *str, (int)pos, (int)len);
	end = ft_strdup((*str) + pos + 1);
	ft_strdel(str);
	*str = ft_strjoin_multi(TRUE, begin, end, NULL);
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

void t_delete_last_char()
{
	char *str = tgetstr("dc", NULL);

	t_move_left();
	tputs(str, ft_strlen(str), ft_putchar);
	//  TODO FREE ?
}

t_bool display_input_left(char *buff, t_command *command)
{
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 68)
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


t_bool display_input_ondelete(char *buff, t_command *command)
{
	if (buff[0] == 127)
	{
		if (command->pos > 0)
			command->pos--;
		t_delete_last_char();
		ft_delete_char(&(command->str), command->pos);
		return (TRUE);
	}
	return (FALSE);
}

t_bool display_input_insert(char *buff, t_command *command)
{
	int i;

	i = 0;
	while (buff[i])
	{
		ft_insert_char(&(command->str), buff[i], command->pos);
		command->pos++;
		ft_putchar(buff[i]);
		i++;
	}
	return (TRUE);
}

t_bool display_input_validate(char *buff, t_command **command)
{
	t_command		*new_command;

	if ('\n' == buff[0])
	{
		ft_printf("\nExecuter `%s`.\n", (*command)->str);
		if(NULL == (*command)->str || '\0' == (*command)->str[0])
			return (TRUE);
		(*command)->pos = ft_strlen((*command)->str);
		new_command =  ft_memalloc(sizeof(t_command));
		new_command->perv = (*command);
		*command = new_command;
		return (TRUE);
	}
	return (FALSE);
}

void display_input(t_command **command)
{
	char	*buff;

	buff = ft_strnew(10);
	while (1) {
		if (read(STDIN_FILENO, buff, 10) > 0)
		{
			if (display_input_ondelete(buff, *command)) {}
			else if (display_input_validate(buff, command)) {}
			else if (display_input_left(buff, *command)) {}
			else if (display_input_insert(buff, *command)) {}
		}
		ft_strclr(buff);
	}
}

char *              shell_input()
{
	t_command		*command;

	command = ft_memalloc(sizeof(t_command));
	t_init();
	t_enable_insert_mode();
	display_input(&command);
	return ft_strnew(0);
}

int              main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	ft_loadenv(environ);
	shell_input();
	return (0);
}