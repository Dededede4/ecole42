/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whereis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 12:20:09 by mprevot           #+#    #+#             */
/*   Updated: 2017/08/06 12:20:25 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_whereis(char *cmd_name)
{
	char	*path;
	char	**paths;
	char	*current;
	char	*r;
	int		i;

	if (access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	i = 0;
	if (!(path = ft_getenv("PATH")))
		return (NULL);
	paths = ft_strsplit(path, ':');
	r = NULL;
	while (paths[i])
	{
		current = ft_strjoin_multi(FALSE, paths[i], "/", cmd_name, NULL);
		if (!r && access(current, X_OK) == 0)
			r = ft_strdup(current);
		ft_strdel(&current);
		ft_strdel(paths + i);
		i++;
	}
	ft_memdel((void**)(&paths));
	return (r);
}
