/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 14:06:53 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/21 13:39:16 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"

char			*get_output_path(char *name)
{
	char		*tmp;

	tmp = ft_strrchr(name, '.');
	if (!tmp)
		return (ft_strdup(".cor"));
	*tmp = '\0';
	return (ft_strjoin_multi(FALSE, name, ".cor", NULL));
}

void			write_instruct(int fdout, t_instruct *current)
{
	int			i;
	int			y;
	void		*val;

	while (current)
	{
		i = 0;
		if (current->opcode)
			write(fdout, ((char*)(&(current->opcode))), 1);
		if (current->argcode)
			write(fdout, ((char*)(&(current->argcode))), 1);
		while (i < current->arg_nbrs)
		{
			y = 0;
			val = &(current->args[i][2]);
			while (y < current->args[i][1])
			{
				write(fdout, &(((char *)val)[current->args[i][1] - 1 - y]), 1);
				y++;
			}
			i++;
		}
		current = current->next;
	}
}

int				main(int argc, char **argv)
{
	char		*output_path;
	int			fdin;
	int			fdout;
	t_header	header;
	t_instruct	*instructs;

	if (argc != 2)
		error("Usage : ./asm mychampion.s\n");
	fdin = open(argv[1], O_RDONLY);
	output_path = get_output_path(argv[1]);
	ft_bzero(&header, sizeof(t_header));
	write_exec_magic(&header);
	write_comment(fdin, &header);
	instructs = compiler_compile(fdin);
	header.prog_size = (unsigned int)get_instruct_size(instructs);
	invert_byte(&header.prog_size);
	fdout = open(output_path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	write(fdout, &header, sizeof(t_header));
	write_instruct(fdout, instructs);
	exit(0);
	return (0);
}
