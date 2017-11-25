#include <curses.h>
#include <term.h>

#include "libft/libft.h"

typedef struct			s_command
{
	unsigned int		*str;
	size_t				pos;
	struct s_command	*prev;
	struct s_command	*next;
	struct s_command	*historic_pos;
}						t_command;