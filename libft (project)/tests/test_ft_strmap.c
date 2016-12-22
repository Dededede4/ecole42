/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:43:09 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 12:56:59 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <ctype.h>

char	change(char c)
{
	return (char)toupper((int)c);
}

int		main(void)
{
	char	str[] = "coucou je suis moi";
	char	*str2 = strdup(str);

	char	cmp[] = "COUCOU JE SUIS MOI";
	char *new = ft_strmap(str, change);

	if (strcmp(str, str2) != 0)
		return (10);
	if (strcmp(cmp, new) != 0)
		return (20);
	return (0);
}

