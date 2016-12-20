/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:07:26 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 16:19:03 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	str1[] = "coucou je suis ";
	char	str2[] = "un string";
	char	cmp[] = "coucou je suis un string";

	char	*new = ft_strjoin(str1, str2);
	if (strcmp(cmp, new) != 0)
		return (10);
	return (0);
}
