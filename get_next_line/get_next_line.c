/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 15:38:32 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/19 13:06:40 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buff		*ft_get_buff(fd)
{
	static t_buff	*lstbuff;
	t_buff			*buff;

	buff = lstbuff;
	while (buff)
	{
		if (buff->fd == fd)
			return (buff);
		buff = buff->next;
	}
	buff = (t_buff *)malloc(sizeof(t_buff));
	if (buff == NULL)
		return (NULL);
	buff->fd = fd;
	buff->n = 0;
	buff->buff = ft_strnew(0);
	if (buff->buff == NULL)
		return (NULL);
	if (!lstbuff)
		lstbuff = buff;
	else
		ft_lstadd(&lstbuff, buff);
	return (buff);
}

int		ft_find_line(t_buff *buff)
{
	char	*rest;
	char	*tmp;
	int		l;

	rest = ft_strchr(buff->buff, '\n');
	if(rest == NULL)
	{
		tmp = ft_strnew(BUFF_SIZE);
		l = read(buff->fd, tmp, BUFF_SIZE);
		if (l > 0)
		{
			ft_strjoin(buff->buff, tmp);
			free(tmp);
			return (ft_find_line(buff->buff)));
		}
		else
		{
			buuf->n = 1;
			return (buff->buff);
		}
	}
	else
	{
		*rest = '\0';
		tmp = buff->buff;
		buff->buff = ++rest;
		return (ft_strdup(tmp));
	}
}

int		get_next_line(const int fd, char **line)
{
	t_buff	buff;

	buff = ft_get_buff(fd);
	if (!buff || buff->n)
		return (NULL);
	*line = ft_find_line(buff);
	return (0);	
}
