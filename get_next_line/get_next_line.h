/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 15:40:29 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/22 12:01:51 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 42

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft/libft.h"

/*
** t_buff store the buffer for a specific fd :
**
** fd is the file descriptor
** *content is the buffer (the pointer can move from \n to \n)
** *content_start save the original buffer pointer (for free())
** ended is equal to 1 if the fd is at the end of the file, otherwise 0.
*/

typedef struct		s_buff
{
	int				fd;
	char			*content;
	char			*content_start;
	int				ended;
	struct s_buff	*next;
}					t_buff;

int					get_next_line(const int fd, char **line);

#endif
