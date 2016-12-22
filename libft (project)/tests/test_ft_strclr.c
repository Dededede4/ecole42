/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strclr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:03:16 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 12:07:41 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	str[] = "coucou je fais bien et toi ?";
	int		max = strlen(str);
	int		i = 0;

	ft_strclr(str);
	while (i < max)
	{
		if (str[i] != '\0')
			return (10);
		i++;
	}
	return (0);
}
