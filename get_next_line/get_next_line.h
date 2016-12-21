/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 15:40:29 by mprevot           #+#    #+#             */
/*   Updated: 2016/12/21 12:00:25 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 42

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft/libft.h"

/* t_buff store the buffer for a specific fd :
 * fd is the file descriptor
 * *buff is the buffer
 * n is the number of \n has been returned in previous runs of get_next line
 */

typedef struct		s_buff
{
	int				fd;
	char			*buff;
	char			*buff_start;
	int				n;
	struct s_buff	*next;
}					t_buff;

int		get_next_line(const int fd, char **line);

#endif
