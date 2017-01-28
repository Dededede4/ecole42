/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strrchr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 13:19:47 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/15 13:21:37 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	str[] = "coucou";

	if (ft_strrchr(str, 'o') != str + 4)
		return (10);

	if (ft_strrchr(str, 'O') != NULL)
		return (20);
	return (0);
}
