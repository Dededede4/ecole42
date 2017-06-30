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



t_params	*readLetters(char *chars, t_params *params)
{
	while (*chars)
	{
		if (*chars == '-')
			chars++;
		if (*chars == 'l')
			params->l = TRUE;
		else if (*chars == 'R')
			params->R = TRUE;
		else if (*chars == 'a')
			params->a = TRUE;
		else if (*chars == 'r')
			params->r = TRUE;
		else if (*chars == 't')
			params->t = TRUE;
		else
		{
			*(chars + 1) = 0;
			ft_putstr_fd("ls: illegal option -- ", STDERR_FILENO);
			ft_putstr_fd(chars, STDERR_FILENO);
			ft_putstr_fd("\nusage: ls [-lRart] [file ...]", STDERR_FILENO);
			exit(0);
		}
		chars++;
	}
	return (params);
}

t_params	*extractParams(int argc, char **argv)
{
	t_params	*params;
	t_path		*paths;
	int 		i;

	i = 1;
	params = malloc(sizeof(*params));
	params->paths = NULL;
	while (i < argc)
	{
		if (argv[i][0] == '-' && ft_strlen(argv[i]) >= 2)
		{
			if (!(readLetters(argv[i], params)))
				return (NULL);
		}
		else
		{
			paths = malloc(sizeof(*paths));
			paths->path = argv[i];
			paths->next = NULL;
			if (params->paths)
			{
				lst_path_add_end(params->paths, paths);
			}
			else
			{
				params->paths = paths;
			}	
		}
		i++;
	}
	if (!params->paths)
	{
		paths = malloc(sizeof(*paths));
		paths->path = "./";
		paths->next = NULL;
		params->paths = paths;
	}
	return (params);
}
