/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:32:04 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/14 14:50:58 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../libft.h"
#include <stdlib.h>

#include <unistd.h>

int		main(void)
{
	char	a[] = "cou\0cou";
	char	b[] = "123456";

	ft_memccpy(a, b, '\0', 7);
	if (memcmp(a, b, 3) != 0)
		return (10);
	
	char	source[] = "oooAooooooo";
	char	destination[] = "123456789";
	char	result[] = "oooA56789";

	memccpy(destination, source, 'A', 10);
	if (memcmp(destination, result, 9) != 0)
		return (20);
	
	char    a1[] = "cou0cou";
	ft_memccpy(a1, b, '\0', 7);
	if (memcmp(a1, b, 7) != 0)
                return (30);
	
	return (0);
}
