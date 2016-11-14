/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strcpy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:38:05 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/14 16:56:17 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../libft.h"

int		main(void)
{
	char	str1[] = "0123456789";
	char	*str2 = malloc(sizeof(char) * 11);

	memset(str2, 'Z', 11);

	ft_strcpy(str2, str1);
	return (strcmp(str1, str2));
}
