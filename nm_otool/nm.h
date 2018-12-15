/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 03:40:30 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/15 03:40:35 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct					s_command
{
	t_list						*bss_numbers;
	t_list						*const_numbers;
	t_list						*data_numbers;
	t_list						*text_numbers;

}								t_command;

typedef	struct					s_line
{
	uint64_t					left;
	char						middle;
	char						*right;
	t_bool						is_64;
	t_bool						is_32;
	struct s_line				*next;
}								t_line;

int								antitroll(char *ptr, off_t size);
unsigned int					ft_nxswaplong(unsigned int nbr);
void							handle_64_segment(void *lc, int *ycount);
void							handle_64(char *ptr);
void							handle_32_segment(void *lc, int *ycount);
void							handle_32(char *ptr);
t_bool							lookfor(uint8_t n_sect, t_list *lst);
char							get_type_lookfor(uint8_t n_sect);
char							get_type(struct nlist_64 el);
char							get_type_32(struct nlist el);
t_line							*get_line(
	int nsyms, int symoff, int stroff, char *ptr);
t_line							*get_line_32(
	int nsyms, int symoff, int stroff, void *ptr);
void							tri_pourri_lol_switch(
	t_line *line, t_line *before, t_line **first);
void							tri_pourri_lol(t_line **first);
t_bool							can_show_next(t_line *line, t_line *findme);
t_bool							can_show(t_line *first, t_line *findme);
void							print_line(t_line *line);
void							segname2struct_switch(
	int ycount, t_list **data);
void							segname2struct(int ycount, char *sectname);
void							nm(char *ptr);
t_command						*get_command();

#endif
