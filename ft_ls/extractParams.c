/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractParams.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <mprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 15:25:33 by mprevot           #+#    #+#             */
/*   Updated: 2014/12/05 14:11:20 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_bool 		checkLetter(char c, t_params *params)
{
	if (c == 'l')
		params->l = TRUE;
	else if (c == 'R')
		params->R = TRUE;
	else if (c == 'a')
		params->a = TRUE;
	else if (c == 'r')
		params->r = TRUE;
	else if (c == 't')
		params->t = TRUE;
	else if (c == 's')
		params->s = TRUE;
	else if (c == '1')
		;
	else
		return (FALSE);
	return (TRUE);
}

t_params	*readLetters(char *chars, t_params *params)
{
	while (*chars)
	{
		if (*chars == '-' && *(chars + 1) == '-')
			return (params);
		if (*chars == '-')
			chars++;
		if (!checkLetter(*chars, params))
		{
			*(chars + 1) = 0;
			ft_putstr_error(ft_strjoin("ls: illegal option -- ", chars));
			ft_putstr_error("\nusage: ls [-lRart] [file ...]");
			exit(0);
		}
		chars++;
	}
	return (params);
}

void extractParams_1(char *path, t_path *paths, t_params *params)
{
	paths = ft_memalloc(sizeof(*paths));
	paths->path = path;
	paths->next = NULL;
	params->nbr_paths++;
	if (params->paths)
		lst_path_add_end(params->paths, paths);
	else
		params->paths = paths;
}

t_params	*extractParams(int argc, char **argv)
{
	t_params	*params;
	t_path		*paths;
	int 		i;

	i = 1;
	params = ft_memalloc(sizeof(*params));
	while (i < argc)
	{
		if (argv[i][0] == '-' && ft_strlen(argv[i]) >= 2)
			readLetters(argv[i], params);
		else
			extractParams_1(argv[i], paths, params);
		i++;
	}
	if (!params->paths)
	{
		paths = ft_memalloc(sizeof(*paths));
		paths->path = ".";
		paths->next = NULL;
		params->paths = paths;
	}
	return (params);
}
