/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:09:26 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/23 17:09:27 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"

void				invert_byte(unsigned int *val)
{
	int				i;
	unsigned int	revnbr;
	unsigned int	nbr;

	i = 3;
	nbr = *val;
	while (i >= 0)
	{
		((char*)(&revnbr))[i] = ((char*)(&nbr))[0];
		nbr = nbr >> 8;
		i--;
	}
	*val = revnbr;
}

void				write_exec_magic(t_header *header)
{
	header->magic = COREWAR_EXEC_MAGIC;
	invert_byte(&(header->magic));
}

char				*write_comment_get_cmd(
	char *line, t_bool *have_comment, t_bool *have_name)
{
	if (ft_strncmp(line, NAME_CMD_STRING,
		ft_strlen(NAME_CMD_STRING)) == 0 && !*have_name)
	{
		*have_name = TRUE;
		return (NAME_CMD_STRING);
	}
	if (ft_strncmp(line, COMMENT_CMD_STRING,
		ft_strlen(COMMENT_CMD_STRING)) == 0 && !*have_comment)
	{
		*have_comment = TRUE;
		return (COMMENT_CMD_STRING);
	}
	return (NULL);
}

void				write_comment_gnl(
	t_header *header, char *line, char *cmd)
{
	char			*str;
	int				len;

	str = ft_strtrim(line + ft_strlen(cmd));
	len = ft_strlen(str);
	if (*str != '"')
		error("Command don't start by '\"'\n");
	if (str[len - 1] != '"')
		error("Command don't end by '\"'\n");
	if (ft_strcmp(cmd, NAME_CMD_STRING) == 0)
	{
		if (len > PROG_NAME_LENGTH + 2)
			error("Name too long\n");
		ft_bzero(&(header->prog_name), PROG_NAME_LENGTH + 1);
		ft_memcpy(&(header->prog_name), str + 1, len - 2);
	}
	else
	{
		if (len > COMMENT_LENGTH + 2)
			error("Comment too long\n");
		ft_bzero(&(header->comment), COMMENT_LENGTH + 1);
		ft_memcpy(&(header->comment), str + 1, len - 2);
	}
	ft_memdel((void**)&str);
}

void				write_comment(int fdin, t_header *header)
{
	char			*line;
	t_bool			have_comment;
	t_bool			have_name;
	char			*cmd;

	have_comment = FALSE;
	have_name = FALSE;
	line = NULL;
	while (gnl(fdin, &line))
	{
		if (!(line = ft_strtrim_free(&line)))
			error("Can't read source file\n");
		if ((cmd = write_comment_get_cmd(line, &have_comment, &have_name)))
		{
			write_comment_gnl(header, line, cmd);
			if (have_comment && have_name)
				break ;
		}
		else if (!(*line == '\0' || *line == COMMENT_CHAR))
			error("Error in name/description.\n");
		ft_memdel((void**)&line);
	}
	ft_memdel((void**)&line);
	if (!have_comment || !have_name)
		error("Missing comment or name.\n");
}
