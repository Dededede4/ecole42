/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strsub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:28:46 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 16:00:19 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

int		main(void)
{
	char	str[] = "coucou je mange";
	char	cmp[] = "je";
	char	*new = ft_strsub(str, 7, 2);
	if (strcmp(cmp, new) != 0)
		return (10);
	return (0);
}
