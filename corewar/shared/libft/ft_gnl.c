/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 15:38:32 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/22 13:02:46 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_buff				*ft_get_buff(int fd)
{
	static t_buff	*firstbuff;
	t_buff			*buff;
	t_buff			*last;

	buff = firstbuff;
	while (buff)
	{
		if (buff->fd == fd)
			return (buff);
		last = buff;
		buff = buff->next;
	}
	if (!(buff = (t_buff *)malloc(sizeof(t_buff))))
		return (NULL);
	buff->fd = fd;
	buff->ended = 0;
	if (!(buff->content = ft_strnew(0)))
		return (NULL);
	buff->content_start = buff->content;
	buff->next = NULL;
	if (!firstbuff)
		firstbuff = buff;
	else
		last->next = buff;
	return (buff);
}

char				*ft_find_line(t_buff *buff)
{
	char			*rest;
	char			*tmp;
	int				l;

	if (!(rest = ft_strchr(buff->content, '\n')))
	{
		tmp = ft_strnew(BUFF_SIZE);
		if ((l = read(buff->fd, tmp, BUFF_SIZE)) > 0)
		{
			buff->content = ft_strjoin(buff->content, tmp);
			free(buff->content_start);
			buff->content_start = buff->content;
			free(tmp);
			return (ft_find_line(buff));
		}
		free(tmp);
		if (l == 0 && (buff->ended = 1))
			return (buff->content);
		return (NULL);
	}
	*rest = '\0';
	tmp = buff->content;
	buff->content = ++rest;
	return (ft_strdup(tmp));
}

int					ft_gnl(const int fd, char **line)
{
	t_buff			*buff;

	if (fd < 0 || line == NULL)
		return (-1);
	buff = ft_get_buff(fd);
	if (!buff)
	{
		return (-1);
	}
	if (buff->ended)
		return (0);
	*line = ft_find_line(buff);
	if (*line == NULL)
		return (-1);
	if (buff->ended && **line == '\0')
		return (0);
	return (1);
}
