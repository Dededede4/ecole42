/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 20:09:05 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 20:09:06 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_fdsave		getfdsave(void)
{
	t_fdsave	data;

	data.fd0 = dup(0);
	data.fd1 = dup(1);
	data.fd2 = dup(2);
	return (data);
}

void			execute(t_command *command)
{
	t_instruct	*inst;
	t_instruct	*first;

	inst = command2instruct(command);
	first = inst;
	while (inst)
	{
		if (inst->pipe_to_instruct)
		{
			instruct_file2fd_chain(inst);
			inst = instructs_pipe_chain(inst, getfdsave(), -1);
			continue;
		}
		if (inst->pipe_from_file || inst->pipe_to_file || inst->pipe_from_fd)
		{
			instruct_file2fd_chain(inst);
			inst = instruct_pipe_fd(inst);
		}
		else
		{
			exec_instrut_simple(inst);
			inst = inst->next;
		}
	}
	storeinstructs(first);
}
