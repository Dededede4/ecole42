/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 13:29:28 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/15 13:33:45 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	str[] = "je mange des patates";

	if (ft_strstr(str, "mange") != str + 3)
		return (10);

	if (ft_strstr(str, "respect") != NULL)
		return (20);
	
	if (ft_strstr(str, "") != str)
		return (30);

	return (0);
}
