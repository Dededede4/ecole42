/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strncmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 13:55:55 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/15 14:01:32 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	if (ft_strcmp("aaaa", "b") >= 0)
		return (10);
	if (ft_strcmp("bbbbb", "a") <= 0)
		return (20);
	if (ft_strcmp("aaa", "aaa") != 0)
		return (30);
	return (0);
}