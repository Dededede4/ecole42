#include "libft.h"

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"

typedef struct		s_tetri
{
	struct s_tetri	*l;
	struct s_tetri	*r;
	struct s_tetri	*d;
	struct s_tetri	*t;
	char			c;
}					t_tetri;
size_t	ft_strlinelen(char *s);
int		ft_open(char *argc[]);

#endif
