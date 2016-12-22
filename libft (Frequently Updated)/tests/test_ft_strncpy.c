/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strncpy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 17:00:01 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/14 17:18:27 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../libft.h"

int		main(void)
{
	char	source[] = "012345";
	char	*destination = malloc(sizeof(char) * 11);
	char	*attendu = malloc(sizeof(char) * 11);

	memset(attendu, 'Z', 11);
	memset(destination, 'Z', 11);
	
	strncpy(attendu, source, 8);
	ft_strncpy(destination, source, 8);

	return (memcmp(destination, attendu, 11));
}
