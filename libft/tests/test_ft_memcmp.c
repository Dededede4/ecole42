/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_memcmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:29:40 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/14 15:32:58 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	str1[] = "aaaaaaa";
	char	str2[] = "bb";
	char	str3[] = "bb";

	if (ft_memcmp(str1, str2, 7) >= 0)
		return (10);

	if (ft_memcmp(str2, str1, 7) <= 0)
		return (20);

    if (ft_memcmp(str2, str3, 3) != 0)
		return (30);

	return (0);
}
