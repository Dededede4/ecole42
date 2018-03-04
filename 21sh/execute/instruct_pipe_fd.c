/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct_pipe_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 20:05:48 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 20:05:56 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_instruct	*instruct_pipe_fd(t_instruct *instruct)
{
	int savefd2;
	int savefd1;
	int savefd0;

	savefd0 = dup(0);
	savefd1 = dup(1);
	savefd2 = dup(2);
	if (instruct->aggregate_fd)
		dup2(instruct->pipe_to_fd, 2);
	if (instruct->invert_fd)
		dup2(instruct->pipe_to_fd, 1);
	dup2(instruct->pipe_to_fd, 1);
	dup2(instruct->pipe_from_fd, 0);
	exec_instrut_simple(instruct);
	close(instruct->pipe_to_fd);
	close(instruct->pipe_from_fd);
	dup2(savefd0, 0);
	dup2(savefd1, 1);
	dup2(savefd2, 2);
	return (instruct->next);
}
