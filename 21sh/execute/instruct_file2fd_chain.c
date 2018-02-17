/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct_file2fd_chain.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:56:16 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 19:56:23 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void		instruct_file2fd(t_instruct *instruct)
{
	int val;

	val = O_WRONLY | O_CREAT;
	if (instruct->pipe_from_file)
		instruct->pipe_from_fd = open(instruct->pipe_from_file, O_RDONLY);
	if (instruct->replace_file)
		val = val | O_TRUNC;
	else
		val = val | O_APPEND;
	if (ft_strequ(instruct->pipe_to_file, "&1"))
	{
		ft_strdel(&(instruct->pipe_to_file));
		instruct->pipe_to_file = NULL;
		instruct->pipe_to_fd = dup(1);
	}
	else if (ft_strequ(instruct->pipe_to_file, "&-"))
		instruct->pipe_to_fd = open("/dev/null", O_WRONLY);
	else if (instruct->pipe_to_file)
		instruct->pipe_to_fd = open(instruct->pipe_to_file, val, 0755);
}

void		instruct_file2fd_chain(t_instruct *instruct)
{
	while (instruct)
	{
		instruct_file2fd(instruct);
		instruct = instruct->pipe_to_instruct;
	}
}
