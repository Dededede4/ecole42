/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strtrim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:14:54 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 17:34:38 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	str[] = "	   coucou   	";
	char	cmp[] = "coucou";

	char	*new = ft_strtrim(str);
	if (strcmp(cmp, new) != 0)
		return (10);

	if ( new >= str && new <= str + strlen(str))
		return (20);
	
	return (0);
}
