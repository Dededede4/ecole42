
#include "../main.h"

t_bool				display_input_supermoves_end(
	unsigned int buff, t_command *command)
{
	struct winsize	w;
	int				i;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	i = 0;
	if (buff == MOVE_END)
	{
		display_input_right(MOVE_RIGHT, command);
		while (command->pos < ft_uintlen(command->str))
		{
			display_input_right(MOVE_RIGHT, command);
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool				display_input_supermoves_home(
	unsigned int buff, t_command *command)
{
	struct winsize	w;
	int				i;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	i = 0;
	if (buff == MOVE_HOME)
	{
		if (command->pos != 0)
			display_input_left(MOVE_LEFT, command);
		while (command->pos != 0)
		{
			display_input_left(MOVE_LEFT, command);
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool				display_input_supermoves_homeend(
	unsigned int buff, t_command *command)
{
	if (display_input_supermoves_home(buff, command))
		return (TRUE);
	if (display_input_supermoves_end(buff, command))
		return (TRUE);
	return (FALSE);
}