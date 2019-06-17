/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:31:46 by heynard           #+#    #+#             */
/*   Updated: 2017/06/17 14:57:31 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

static int		check_buffer(char **buffer, char **line)
{
	char		*tmp;

	if ((tmp = ft_strchr(*buffer, '\n')))
	{
		*tmp = '\0';
		*line = ft_strdup(*buffer);
		*buffer = ft_strdup(tmp + 1);
		tmp = NULL;
		return (1);
	}
	return (0);
}

static int		check_tmp_buf(char *tmp_buf, char **buffer, char **line)
{
	char		*tmp;

	tmp = ft_strchr(tmp_buf, '\n');
	if (tmp != NULL)
	{
		*tmp = '\0';
		*line = ft_strjoin(*buffer, tmp_buf);
		free(*buffer);
		*buffer = ft_strdup(tmp + 1);
		tmp = NULL;
		free(tmp_buf);
		return (1);
	}
	return (0);
}

static int		norminette(int fd, char *tmp_buf, char **buffer, char **line)
{
	char		*tmp;
	int			ret;

	while ((ret = read(fd, tmp_buf, BUFF_SIZE)) > 0)
	{
		tmp_buf[ret] = '\0';
		if (check_tmp_buf(tmp_buf, buffer, line) == 1)
			return (1);
		tmp = *buffer;
		*buffer = ft_strjoin(*buffer, tmp_buf);
		free(tmp);
	}
	if (ret < 0)
		return (-1);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char	*buffer = NULL;
	char		*tmp_buf;
	int			ret;

	if (buffer != NULL)
		if (check_buffer(&buffer, line) == 1)
			return (1);
	tmp_buf = ft_strnew(BUFF_SIZE);
	if ((ret = norminette(fd, tmp_buf, &buffer, line)) == 1)
		return (1);
	ft_strdel(&tmp_buf);
	if (ret < 0)
		return (-1);
	if (buffer == NULL || buffer[0] == '\0')
		return (0);
	*line = ft_strdup(buffer);
	free(buffer);
	buffer = NULL;
	return (1);
}
