/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 21:09:12 by mprevot           #+#    #+#             */
/*   Updated: 2018/02/16 21:09:13 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <curses.h>
# include <term.h>
# include <signal.h>
# include <errno.h>

# include <sys/ioctl.h>
# include "libft/libft.h"

# define SUPERMOVE_LEFT	1146821403
# define SUPERMOVE_RIGHT	1130044187
# define SUPERMOVE_DOWN	1113266971
# define SUPERMOVE_UP	1096489755

# define MOVE_LEFT		4479771
# define MOVE_RIGHT		4414235
# define MOVE_TOP		4283163
# define MOVE_DOWN		4348699
# define MOVE_HOME 		4741915
# define MOVE_END		4610843

# define ACTION_COPY		7011
# define ACTION_PAST		7024
# define ACTION_CUT		6979
# define ACTION_SELECT	7027

# define KEY_ESC			27

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
	t_command			*command;
}						t_container;

typedef struct			s_token
{
	unsigned int		*str;
	t_bool				ignore_me;
	struct s_token		*next;
}						t_token;

typedef struct			s_instruct
{
	unsigned int		*program_name;
	t_token				*program_args;
	int					pipe_to_fd;
	int					pipe_from_fd;
	char				*pipe_from_str;
	struct s_instruct	*pipe_to_instruct;
	t_bool				replace_file;
	char				*pipe_from_file;
	char				*pipe_to_file;
	t_bool				aggregate_fd;
	t_bool				invert_fd;
	struct s_instruct	*next;
}						t_instruct;

typedef struct			s_fdsave
{
	int					fd0;
	int					fd1;
	int					fd2;
}						t_fdsave;

void					ft_insert_char(
	unsigned int **str, unsigned int c, size_t pos);
void					ft_delete_char(unsigned int **str, size_t pos);
void					t_init(t_bool save);
void					t_save(void);
void					t_restore(void);
t_bool					t_delete_after_cursor(void);
t_bool					t_start_under(void);
t_bool					t_stop_under(void);
t_bool					t_enable_insert_mode(void);
t_bool					t_disable_insert_mode(void);
t_bool					t_move_left(void);
t_bool					t_move_right(void);
t_bool					t_delete_last_char(void);
void					clear_input(t_command *command);
void					clear_input_soft(t_command *command);
t_bool					display_input_ondelete(
	unsigned int buff, t_command *command);
t_bool					display_input_insert(
	unsigned int buff, t_command *command);
void					execute(t_command *command);
t_bool					display_input_copypast(
	unsigned int buff, t_command *command, unsigned int **clipboard);
t_bool					display_input_right(
	unsigned int buff, t_command *command);
void					show_command(t_command *command);
t_bool					display_input_left2(char *buff, t_command *command);
t_bool					display_input_left(
	unsigned int buff, t_command *command);
int						ft_putchar2(int c);
void					complete_buff(unsigned int *buff);
t_bool					display_input_validate(
	unsigned int buff, t_command **command);
t_bool					display_input_supermoves(
	unsigned int buff, t_command *command);
t_bool					display_input_historic(
	unsigned int buff, t_command *command);
char					*display_input_heredoc(char *stop);
void					show_command(t_command *command);
void					sig_handler(int signo);
size_t					get_word_pos(unsigned int *str, size_t start);
unsigned int			*clear_escapes(unsigned int *str);
t_token					*tokenize(unsigned int *str);
t_token					*deltoken(t_token **delme);
int						heredoc(char *stop);
void					command2instruct_redirect1(
	t_token *arg, t_token *lastarg, t_instruct *instruct);
void					command2instruct_redirect2(
	t_token *arg, t_token *lastarg, t_instruct *instruct);
void					command2instruct_redirect3(
	t_token *arg, t_token *lastarg, t_instruct *instruct);
void					command2instruct_redirect4(
	t_token *arg, t_token *lastarg, t_instruct *instruct);
t_bool					command2instruct_redirect5(
	t_token **arg, t_token *lastarg, t_instruct **instruct);
t_instruct				*command2instruct(t_command *command);
t_instruct				*instructs_pipe_chain(
	t_instruct *instruct, t_fdsave fds, int fd);
void					exec_instrut_simple(t_instruct *instruct);
void					ft_execwait(char *path, char **av);
char					**instruct_to_agrv(t_instruct *instruct, int *argc);
void					log_and_chdir(char *path);
void					execbuiltin_cd(char **argv);
t_bool					execbuiltin(char **argv);
void					putargv(char **argv);
void					del_argv(char **argv, int argc);
void					instruct_file2fd_chain(t_instruct *instruct);
void					exec_instrut_simple(t_instruct *instruct);
t_instruct				*instruct_pipe_fd(t_instruct *instruct);
void					storeinstructs(t_instruct *instruct);
t_bool					display_input_supermoves_homeend(
	unsigned int buff, t_command *command);
#endif
