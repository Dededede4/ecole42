/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:47:58 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/24 16:17:17 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** 1 regarde si dans le tampon il y a une /n
** 		si oui renvoie la partie de la ligne avec \n et stoque un pointeur de
** l'endroit d'arret puis fin de la fonction.
** 2 si non lit la premiere boucle colle le resultat avec le tampon(s'il y a)
** free le tampon
**		puis regarde dans la boucle si il y a un \n
**		si oui, renvoie la partie de la ligne avec un \n et stoque l'endroit ou
** il s'est arreter puis fin de la fonction.
**		la string devient le tampon
*/

int			memfind(void *str, size_t len)
{
	size_t		i;

	i = 0;
	if (len != 0 && (((char *)str)[i] == '\n' || ((char *)str)[i] == 26))
		i++;
	while (i < len && ((char *)str)[i] != '\n' && ((char *)str)[i] != 26)
	{
		if (((char *)str)[i] == '\n' || ((char *)str)[i] == 26)
			break ;
		i++;
	}
	if (i == len)
		return (0);
	return (i);
}

int			verif(char **line, void *string, int len, t_fd *mail)
{
	int		i;
	int		j;
	void	*tampon;

	i = 0;
	j = 0;
	while (((char *)string)[i] != '\n' && ((char *)string)[i] != 26 && i < len)
		i++;
	if (!(*line = ft_memalloc(sizeof(char) * i + 1)))
		return (-1);
	while (i > j)
	{
		line[0][j] = ((char *)string)[j];
		j++;
	}
	if (!(tampon = ft_memalloc(len - j + 1)))
		return (-1);
	if (((char *)string)[j] == '\n' || ((char *)string)[j] == 26)
		j++;
	mail->lastbuff = 0;
	while (j < len)
		((char *)tampon)[mail->lastbuff++] = ((char *)string)[j++];
	mail->tampon = tampon;
	free(string);
	return (1);
}

int			concat(t_fd *mail, void **buff, int *j)
{
	void	*tmp;
	int		i;

	i = *j;
	if (!(tmp = ft_memalloc(sizeof(char) * mail->lastbuff + i + 1)))
		return (-1);
	if (mail->tampon)
	{
		ft_memcpy(tmp, mail->tampon, mail->lastbuff + 1);
		free(mail->tampon);
	}
	ft_memcpy(&tmp[mail->lastbuff], buff[0], i + 1);
	mail->lastbuff = mail->lastbuff + i;
	mail->tampon = tmp;
	return (0);
}

int			read_my_line(t_fd *mail, char **line)
{
	int		i;
	void	*buff;

	if (memfind(mail->tampon, mail->lastbuff) > 0)
		return (verif(line, mail->tampon, mail->lastbuff, mail));
	i = BUFF_SIZE;
	if (!(buff = ft_memalloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	while (i == BUFF_SIZE)
	{
		if ((i = read(mail->fd_n, buff, BUFF_SIZE)) < 1 && mail->lastbuff == 0)
			break ;
		if (concat(mail, &buff, &i) == -1)
			return (-1);
		if (i != BUFF_SIZE || memfind(mail->tampon, mail->lastbuff) > 0)
		{
			free(buff);
			return (verif(line, mail->tampon, mail->lastbuff, mail));
		}
	}
	free(buff);
	return (0);
}

int			ft_gnl(const int fd, char **line)
{
	static t_fd		*begin = NULL;
	t_fd			*list;
	t_fd			*mail;

	if (fd < 0 || !line || (line[0] = NULL) != NULL || read(fd, *line, 0) == -1)
		return (-1);
	list = begin;
	while (list && list->next && list->fd_n != fd)
		list = list->next;
	if (!list || list->fd_n != fd)
	{
		mail = malloc(sizeof(t_fd));
		mail->next = NULL;
		mail->tampon = NULL;
		mail->fd_n = fd;
		mail->lastbuff = 0;
		if (!begin)
			begin = mail;
		else
			list->next = mail;
		return (read_my_line(mail, line));
	}
	return (read_my_line(list, line));
}
