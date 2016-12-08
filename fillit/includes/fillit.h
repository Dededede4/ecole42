#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# include <string.h>
# include <errno.h>
# include <stdio.h>

typedef struct		s_tetri
{
	struct s_tetri	*l;
	struct s_tetri	*r;
	struct s_tetri	*d;
	struct s_tetri	*t;
	char			c;
	char			printed;
}					t_tetri;
int		ft_strlinelen(char *s);
int		ft_open(char *path);
t_tetri	**creat_tetriminos(char *path, int nbr);
void	ft_permute(void	**str, int len, int start);
t_tetri	**reader(int argc, char *path, int *len);
void	ft_merge_tetriminos(char *map, int width, t_tetri *tetri, int pos);
void	*ft_getmap(int width);

#endif
