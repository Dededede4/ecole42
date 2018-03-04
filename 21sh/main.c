/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 10:59:48 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/13 10:59:50 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_command			*currentcommand;

void					cc_clear(t_command *command)
{
	command->cc_pos_start = 0;
	command->cc_pos_stop = 0;
	command->cc_mode_enabled = 0;
}

void					display_input_actions(
	unsigned int buff, unsigned int **clipboard, t_command **command)
{
	if (display_input_ondelete(buff, *command))
		cc_clear(*command);
	else if (display_input_validate(buff, command))
		cc_clear(*command);
	else if (display_input_supermoves(buff, *command) ||
		display_input_supermoves_homeend(buff, *command) ||
		display_input_left(buff, *command) ||
		display_input_right(buff, *command)
		)
		;
	else if (display_input_historic(buff, *command))
		cc_clear(*command);
	else if (display_input_copypast(buff, *command, clipboard))
		;
	else if (display_input_insert(buff, *command))
		cc_clear(*command);
}

void					display_input(t_command **command)
{
	unsigned int	buff;
	unsigned int	*clipboard;

	buff = 0;
	clipboard = NULL;
	ft_putstr("$> ");
	while (read(STDIN_FILENO, &buff, 1) > 0)
	{
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
		display_input_actions(buff, &clipboard, command);
		currentcommand = *command;
		buff = 0;
	}
}

unsigned int			*shell_input(void)
{
	t_command		*command;

	command = ft_memalloc(sizeof(t_command));
	currentcommand = command;
	t_init(TRUE);
	t_enable_insert_mode();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTERM, sig_handler);
	display_input(&command);
	return (ft_uintnew(0));
}

int						main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	ft_loadenv(environ);
	shell_input();
	return (0);
}
