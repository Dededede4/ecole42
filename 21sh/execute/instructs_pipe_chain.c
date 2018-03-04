/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructs_pipe_chain.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:06:46 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 19:06:56 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void exec_instrut_simple_nowait(t_instruct *instruct)
{
	pid_t	father;

	father = fork();
	if (father > 0)
	{
		//wait(&osef);
	}
	else
	{
		exec_instrut_simple(instruct);
		exit(0);
	}
}

void 		display_fd(int fd)
{
	char 	str[1001];
	int 	end;

	while ((end = read(fd, str, 1000)) > 0)
	{
		str[end] = '\0';
		ft_putstr(str);
	}
}

void		instructs_pipe_chain_1(
	t_instruct *instruct, int savefd1, int savefd2, int (*p)[2])
{
	int		c[2];

	pipe((*p));
	dup2(instruct->pipe_from_fd, 0);
	if (instruct->aggregate_fd)
		dup2((*p)[1], 2);
	if (instruct->invert_fd)
	{
		pipe(c);
		dup2(c[1], 1);
	}
	else
		dup2((*p)[1], 1);
	exec_instrut_simple_nowait(instruct);
	if (instruct->invert_fd)
	{
		dup2(savefd1, 1);
		close(c[1]);
		display_fd(c[0]);
	}
	close((*p)[1]);
	dup2(savefd2, 2);
	close(instruct->pipe_from_fd);
}

void		instructs_pipe_chain_2(
	int fd, t_instruct *instruct, int savefd2, int (*p)[2])
{
	int		c[2];

	dup2(fd, 0);
	pipe((*p));
	dup2((*p)[1], 1);
	if (instruct->aggregate_fd)
		dup2((*p)[1], 2);
	if (instruct->invert_fd)
	{
		pipe(c);
		dup2(c[1], 1);
		dup2(c[0], 2);
	}
	exec_instrut_simple_nowait(instruct);
	close((*p)[1]);
	dup2(savefd2, 2);
}

void		instructs_pipe_chain_3(
	t_instruct *instruct, t_fdsave fds, int fd)
{
	int		c[2];

	dup2(fd, 0);
	dup2(instruct->pipe_to_fd, 1);
	if (instruct->aggregate_fd)
		dup2(instruct->pipe_to_fd, 2);
	if (instruct->invert_fd)
	{
		pipe(c);
		dup2(c[1], 1);
		dup2(c[0], 2);
	}
	exec_instrut_simple_nowait(instruct);
	dup2(fds.fd0, 0);
	dup2(fds.fd1, 1);
	dup2(fds.fd2, 2);
}

t_instruct	*instructs_pipe_chain(
	t_instruct *instruct, t_fdsave fds, int fd)
{
	int		p[2];
	static	int test = 0;
	int osef = 0;

	test++;
	if (instruct->pipe_to_instruct)
	{
		if (-1 == fd)
		{
			instructs_pipe_chain_1(instruct, fds.fd1, fds.fd2, &p);
			return (instructs_pipe_chain(
				instruct->pipe_to_instruct, fds, p[0]));
		}
		else
		{
			instructs_pipe_chain_2(fd, instruct, fds.fd2, &p);
			return (instructs_pipe_chain(
				instruct->pipe_to_instruct, fds, p[0]));
		}
	}
	else
	{
		instructs_pipe_chain_3(instruct, fds, fd);
		while(test--)
		{
			wait(&osef);
		}
		test = 0;
		return (instruct->next);
	}
}
