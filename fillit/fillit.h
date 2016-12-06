#include "libft.h"

typedef struct		s_tetri
{
	struct s_tetri	*l;
	struct s_tetri	*r;
	struct s_tetri	*d;
	struct s_tetri	*t;
}					t_tetri;

size_t	ft_strlinelen(char *s)