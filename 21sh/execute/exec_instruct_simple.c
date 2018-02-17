/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_instruct_simple.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:59:07 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 19:59:09 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	exec_instrut_simple(t_instruct *instruct)
{
	char		*tmp;
	char		*whereis;
	t_bool		isbuildin;
	char		**argv;
	int			argc;

	tmp = ft_uint_to_char(instruct->program_name);
	whereis = ft_whereis(tmp);
	ft_memdel((void**)&tmp);
	argc = 0;
	argv = instruct_to_agrv(instruct, &argc);
	isbuildin = execbuiltin(argv);
	if (!isbuildin && !whereis)
	{
		ft_strdel(&whereis);
		ft_putstr_error("Command no found.\n");
		del_argv(argv, argc);
		return ;
	}
	if (!isbuildin)
		ft_execwait(whereis, argv);
	ft_strdel(&whereis);
	del_argv(argv, argc);
}
