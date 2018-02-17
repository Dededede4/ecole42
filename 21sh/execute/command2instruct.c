/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2instruct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 09:27:04 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 09:27:14 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void		command2instruct_split(t_token *token, t_instruct **instruct)
{
	t_token		*arg;

	arg = NULL;
	while (token)
	{
		if (0 == ft_uintcmp(token->str, (unsigned int *)L";") && !(arg = NULL))
		{
			if (!token->next)
				return ;
			token = deltoken(&token);
			(*instruct)->next = ft_memalloc(sizeof(*(*instruct)));
			(*instruct)->pipe_to_fd = dup(1);
			(*instruct) = (*instruct)->next;
			(*instruct)->program_name = ft_uintdup(token->str);
		}
		else
		{
			if (!arg && (arg = ft_memalloc(sizeof(*arg))))
				(*instruct)->program_args = arg;
			else if ((arg->next = ft_memalloc(sizeof(*arg))))
				arg = arg->next;
			arg->str = ft_uintdup(token->str);
		}
		token = deltoken(&token);
	}
}

void		command2instruct_while(t_token **arg, t_instruct **instruct)
{
	t_token		*lastarg;

	(*arg) = (*instruct)->program_args;
	lastarg = NULL;
	while ((*arg) && (*arg)->next)
	{
		if ((*arg)->ignore_me)
		{
			(*arg) = (*arg)->next;
			continue;
		}
		command2instruct_redirect1((*arg), lastarg, (*instruct));
		command2instruct_redirect2((*arg), lastarg, (*instruct));
		command2instruct_redirect3((*arg), lastarg, (*instruct));
		command2instruct_redirect4((*arg), lastarg, (*instruct));
		if (!command2instruct_redirect5(arg, lastarg, instruct))
		{
			lastarg = (*arg);
			if ((*arg))
				(*arg) = (*arg)->next;
		}
	}
}

t_instruct	*command2instruct(t_command *command)
{
	t_instruct	*instruct;
	t_instruct	*first_instruct;
	t_token		*token;
	t_token		*arg;

	arg = NULL;
	token = tokenize(command->str);
	if (!token)
		return (NULL);
	instruct = ft_memalloc(sizeof(*instruct));
	instruct->pipe_to_fd = dup(1);
	instruct->program_name = ft_uintdup(token->str);
	first_instruct = instruct;
	token = deltoken(&token);
	command2instruct_split(token, &instruct);
	instruct = first_instruct;
	while (instruct)
	{
		command2instruct_while(&arg, &instruct);
		instruct = instruct->next;
	}
	return (first_instruct);
}
