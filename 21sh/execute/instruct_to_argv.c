/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct_to_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:41:26 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 19:41:44 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char			**instruct_to_agrv(t_instruct *instruct, int *argc)
{
	t_token		*arg;
	int			size;
	char		**argv;
	size_t		i;

	i = 0;
	arg = instruct->program_args;
	size = 0;
	while (arg)
	{
		if (!arg->ignore_me)
			size++;
		arg = arg->next;
	}
	*argc = size + 2;
	arg = instruct->program_args;
	argv = (char **)ft_memalloc(sizeof(char*) * (size + 2));
	argv[i++] = ft_uint_to_char(instruct->program_name);
	while (arg)
	{
		if (!arg->ignore_me)
			argv[i++] = ft_uint_to_char(arg->str);
		arg = arg->next;
	}
	return (argv);
}
