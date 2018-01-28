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
	size_t				cc_pos_start;
	size_t				cc_pos_stop;
	t_bool				cc_mode_enabled;
}						t_command;

typedef struct			s_container
{
	char				*clipboard;
	t_command			*t_command;
}						t_container;



typedef struct			s_token
{
	unsigned int 		*str;
	t_bool				ignore_me;
	struct s_token		*next;
}						t_token;

typedef struct			s_instruct
{
	unsigned int		*program_name;
	t_token				*program_args;
	int 				pipe_to_fd;
	int 				pipe_from_fd;
	char 				*pipe_from_str;
	struct s_instruct	*pipe_to_instruct;
	t_bool				replace_file;
unsigned int		*pipe_from_file;
unsigned int		*pipe_to_file;
t_bool				aggregate_fd;
//	int					stdrr;
//	int					stdin;
//	int					stout;
	struct s_instruct	*next;
}					t_instruct;
