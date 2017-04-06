/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 21:03:33 by mprevot           #+#    #+#             */
/*   Updated: 2017/03/23 21:03:34 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPILER_H
# define COMPILER_H

# include "../includes/corewar.h"
# include "../includes/libft/libft.h"

/*
**[arg_type, content_len, octet1, octet2, octet3, octet4]
*/

typedef struct			s_instruct
{
	char				*label_name;
	size_t				size;
	int					opcode;
	int					argcode;
	int					arg_nbrs;
	int					args[3][3];
	char				*args_labels[3];
	struct s_instruct	*next;
}						t_instruct;

void					write_exec_magic(t_header *header);
void					write_comment(int fdin, t_header *header);
void					error(char *str);
t_instruct				*compiler_compile(int fdin);
size_t					get_instruct_size(t_instruct *current);
void					invert_byte(unsigned int *val);
int						compiler_compile_get_label(char *line);
int						get_argtype(char *str, int conf);
char					*extract_str(char *str);
int						extract_int(char *str);
size_t					get_instruct_size(t_instruct *current);
void					instructs_add(
	t_instruct **instructs_list, t_instruct *instruct);
size_t					get_label_position(t_instruct *first, char *labelname);
size_t					get_request_label_position(
	t_instruct *first, t_instruct *tofind);
size_t					get_relative(
	t_instruct *first, t_instruct *tofind, char *labelname);
void					hydrate_labels(t_instruct *first);
t_op					get_config(char *name);
t_op					corewar_op_name2tab(char *name);
int						gnl(const int fd, char **line);
#endif
