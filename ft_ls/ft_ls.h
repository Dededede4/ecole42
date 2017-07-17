/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <mprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 16:02:00 by mprevot           #+#    #+#             */
/*   Updated: 2015/01/30 19:41:42 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>

typedef	struct		s_file
{
	char			right[10];
	char			type;
	int				links;
	char			*owner;
	char			*group;
	size_t			bytes;
	struct timespec	modified;
	struct timespec lstacess;
	struct timespec lststatchg;
	time_t			mtime;
	char			*name;
	char			*dir;
	char			*path;
	char			*path_link;
	int				major;
	int				minor;
	int				fd;
	int				blocks;
	char			*error;
	struct s_file	*next;
}					t_file;

typedef struct		s_path
{
	char			*path;
	struct s_path	*next;
}					t_path;

typedef struct		s_width
{
	int				links;
	int				owner;
	int				group;
	int				bytes;
	int				minor;
	int				major;
}					t_width;

typedef struct		s_params
{
	t_bool			l;
	t_bool			rr;
	t_bool			a;
	t_bool			r;
	t_bool			t;
	t_bool			s;
	int				nbr_paths;
	struct s_path	*paths;
}					t_params;

void				lst_file_add_end(t_file *file, t_file *new_file);
void				lst_path_add_end(t_path *file, t_path *new_file);
t_params			*extractparams(int argc, char **argv);
t_file				*findfiles(t_path *path);
void				sort_display(t_path	*pcur, t_file *file, t_params *params);
void				long_display(t_path	*pcur, t_file *file, t_params *params);
char				*get_date(const time_t *clock);
void				bubblesort(
	void **data, int (*f)(void *, void *), size_t len);
size_t				lst_len(t_file *file);
t_file				**lst_to_tab(t_file *file, size_t *i);
void				tab_to_lst(t_file **data, size_t i);
t_file				*recursive_long_display(
	t_path *pcur, t_file *file, t_params *param);
t_file				*sort_lst(t_file *f, int (*func)(void*, void*));
int					tri_asc_size(void *f1, void *f2);
int					tri_asc_time(void *f1, void *f2);
int					tri_asc_ascii(void *f1, void *f2);
t_file				*sort_lst_revert(t_file *f);
void				tab_to_lst_path(t_path **data, size_t len);
t_path				**lst_to_tab_path(t_path *file, size_t *i);
t_path				*sort_lst_path(t_path *f, int (*func)(void*, void*));
int					tri_asc_ascii_path(void *f1, void *f2);
size_t				lst_len_path(t_path *file);
int					tri_asc_size_path(void *f1, void *f2);
int					tri_asc_time_path(void *f1, void *f2);
t_path				*sort_lst_revert_path(t_path *f);
int					isdirectory(const char *path);
void				set_width(t_width *width, t_file *file);
t_width				*calculate_cols(t_file *file, t_params *params);
void				sort_display(t_path *pcur, t_file *file, t_params *params);
void				ll_total(t_file *file, t_params *params);
void				long_display_1(
	t_path *pcur, t_file *file, t_params *params);
void				long_display_while_1(t_file *file, t_width *width);
void				long_display_while_2(t_file *file, t_width *width);
void				long_display_while_3(t_file *file);
char				type_to_char(mode_t c);
void				get_right(t_file *file, struct stat fstat);
char				*find_name_by_path(char *path);
void				set_right(t_file *file);
char				*find_folder_by_path(char *path);
t_file				*sort_lst_revert(t_file *f);
t_path				*sort_lst_revert_path(t_path *f);
int					tri_asc_size_path(void *f1, void *f2);
int					tri_asc_time_path(void *f1, void *f2);
int					tri_asc_ascii_path(void *f1, void *f2);
int					tri_asc_size(void *f1, void *f2);
int					tri_asc_time(void *f1, void *f2);
int					tri_asc_ascii(void *f1, void *f2);
int					get_bytes(char *path);
time_t				get_time(char *path);
#endif
