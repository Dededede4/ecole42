#include "minishell.h"

void		execute(char *cammand)
{
	// Trouver la command dans PATH
	// echo ; cd ; setenv ; unsetenv ; env ; exit

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
