/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bzero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 13:46:11 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/11 14:28:47 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../libft.h"
#include <stdlib.h>

int		main(void)
{
	char	a[] = "coucou";
	ft_bzero(a, 3);
	
	char	b[] = "coucou";
	bzero(b, 3);

	return memcmp(a, b, 7);
}
