/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_date.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <mprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 11:18:20 by mprevot           #+#    #+#             */
/*   Updated: 2014/12/05 13:55:15 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*strjoin_free(char *str1, char *str2)
{
	char	*strnew;

	strnew = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (strnew);
}

char	*rm_sec(char *str)
{
	char	**data;
	char	*s;

	data = ft_strsplit(str, ':');
	s = ft_strjoin(data[0], ":");
	free(data[0]);
	return (ft_strjoin(s, data[1]));
}

char	*get_date(const time_t *clock)
{
	char	*str;
	char	**data;
	char	*tmp;

	str = ctime(clock);
	data = ft_strsplit(str, ' ');
	tmp = strjoin_free(data[1], ft_strdup(" "));
	tmp = strjoin_free(tmp, data[2]);
	tmp = strjoin_free(tmp, ft_strdup(" "));
	tmp = strjoin_free(tmp, rm_sec(data[3]));
	free(data);
	return (tmp);
}
