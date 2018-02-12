#include "main.h"

void cc_clear(t_command *command)
{
	command->cc_pos_start = 0;
	command->cc_pos_stop = 0;
	command->cc_mode_enabled = 0;
}

void show_command(t_command *command)
{
	if (command->str == NULL)
		return;
	ft_uintput(command->str);
	command->pos = ft_uintlen(command->str);
}

extern char **environ;

void sig_handler(int signo)
{
    if (signo == SIGINT)
    {
    }
    if (signo == SIGQUIT || signo == SIGTERM)
    {
    	execve("/usr/bin/reset", (char *[15]){"/usr/bin/reset"}, environ);
    }
}


void enable_signals()
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTERM, sig_handler);

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
			cc_clear(*command);
			continue ;
		}
		if (display_input_ondelete(buff, *command)) {cc_clear(*command);}
		else if (display_input_validate(buff, command)) {cc_clear(*command);}
		else if (display_input_supermoves(buff, *command)){}
		else if (display_input_left(buff, *command)) {}
		else if (display_input_right(buff, *command)) {}
		else if (display_input_historic(buff, *command)) {cc_clear(*command);}
		else if (display_input_copypast(buff, *command, &clipboard)) {}
		else if (display_input_insert(buff, *command)) {cc_clear(*command);}
		buff = 0;
	}
}

unsigned int *              shell_input()
{
	t_command		*command;

	command = ft_memalloc(sizeof(t_command));
	t_init(TRUE);
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