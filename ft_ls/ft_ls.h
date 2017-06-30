/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 19:37:23 by mprevot           #+#    #+#             */
/*   Updated: 2017/06/27 20:31:35 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

typedef struct			s_inputsize
{
	int							col1;
	int							col2;
	int							col3;
	int							col4;
	int							col5;
}						t_inputsize;

typedef struct      s_path
{
	char            *path;
	struct s_path   *next;
}                   t_path;

typedef struct      s_params
{
	t_bool			l;
	t_bool			R;
	t_bool			a;
	t_bool			r;
	t_bool			t;
	struct s_path	*paths;
}					t_params;

t_params        *extractParams(int argc, char **argv);
t_params        *readLetters(char *chars, t_params *params);

