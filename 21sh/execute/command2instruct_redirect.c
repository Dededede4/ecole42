/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2instruct_redirect.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 12:05:02 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 12:05:09 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void		command2instruct_redirect1(
	t_token *arg, t_token *lastarg, t_instruct *instruct)
{
	if ('>' == *arg->str && '>' == *arg->next->str)
	{
		if (arg->next->next)
		{
			instruct->pipe_to_file = ft_uint_to_char(arg->next->next->str);
			arg->next->next->ignore_me = TRUE;
		}
		instruct->replace_file = FALSE;
		if (lastarg && 0 == ft_uintcmp(lastarg->str, (unsigned int *)L"2"))
		{
			instruct->aggregate_fd = TRUE;
			lastarg->ignore_me = TRUE;
		}
		if (lastarg && 0 == ft_uintcmp(lastarg->str, (unsigned int *)L"1"))
		{
			instruct->invert_fd = TRUE;
			lastarg->ignore_me = TRUE;
		}
		arg->ignore_me = TRUE;
		arg->next->ignore_me = TRUE;
	}
}

void		command2instruct_redirect2(
	t_token *arg, t_token *lastarg, t_instruct *instruct)
{
	(void)lastarg;
	if ('<' == *arg->str && '<' == *arg->next->str)
	{
		arg->ignore_me = TRUE;
		arg->next->ignore_me = TRUE;
		if (arg->next->next)
		{
			instruct->pipe_from_fd =
				heredoc(ft_uint_to_char(arg->next->next->str));
			arg->next->next->ignore_me = TRUE;
		}
		else
			instruct->pipe_from_fd = heredoc(ft_strdup("<<"));
	}
}

void		command2instruct_redirect3(
	t_token *arg, t_token *lastarg, t_instruct *instruct)
{
	if ('>' == *arg->str && '>' != *arg->next->str)
	{
		if (lastarg && 0 == ft_uintcmp(lastarg->str, (unsigned int *)L"2"))
		{
			instruct->aggregate_fd = TRUE;
			lastarg->ignore_me = TRUE;
		}
		if (lastarg && 0 == ft_uintcmp(lastarg->str, (unsigned int *)L"1"))
		{
			instruct->invert_fd = TRUE;
			instruct->pipe_to_fd = 1;
			lastarg->ignore_me = TRUE;
		}
		instruct->pipe_to_file = ft_uint_to_char(arg->next->str);
		instruct->replace_file = TRUE;
		arg->ignore_me = TRUE;
		arg->next->ignore_me = TRUE;
	}
}

void		command2instruct_redirect4(
	t_token *arg, t_token *lastarg, t_instruct *instruct)
{
	(void)lastarg;
	if ('<' == *arg->str && '<' != *arg->next->str)
	{
		instruct->pipe_from_file = ft_uint_to_char(arg->next->str);
		arg->ignore_me = TRUE;
		arg->next->ignore_me = TRUE;
	}
}

t_bool		command2instruct_redirect5(
	t_token **arg, t_token *lastarg, t_instruct **instruct)
{
	t_instruct *tmpinstruct;

	if ('|' == *(*arg)->str && (*arg)->next && '|' != *(*arg)->next->str)
	{
		(*arg) = deltoken(&(*arg));
		if (lastarg == NULL)
			(*instruct)->program_args = NULL;
		else
			lastarg->next = NULL;
		tmpinstruct = (*instruct)->next;
		(*instruct)->pipe_to_instruct =
			ft_memalloc(sizeof(*((*instruct)->pipe_to_instruct)));
		(*instruct)->pipe_to_instruct->pipe_to_fd = dup(1);
		(*instruct)->pipe_to_instruct->program_name = ft_uintdup((*arg)->str);
		if ((*arg)->next && '|' != *(*arg)->next->str)
			(*instruct)->pipe_to_instruct->program_args = (*arg)->next;
		(*instruct) = (*instruct)->pipe_to_instruct;
		(*instruct)->next = tmpinstruct;
		*arg = deltoken(arg);
		return (TRUE);
	}
	return (FALSE);
}
