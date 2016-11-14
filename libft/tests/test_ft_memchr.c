/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_memchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:04:03 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/14 15:17:39 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../libft.h"

int		main(void)
{
	char	str[] = "je.cherche 1 truc";

	void	*result = ft_memchr(str, '.', strlen(str));

	if (result != str + 2)
		return (10);
	
	void    *result2 = ft_memchr(str, 'X', strlen(str));
	if (result2 != NULL)
		return (20);

	return (0);
}
