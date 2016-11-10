/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:05:48 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/10 10:47:41 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/display_file.h"

int		main(int argc, char **argv)
{
	if (argc > 2)
	{
		ft_putstr("Too many arguments.\n");
		return (0);
	}
	if (argc < 2)
	{
		ft_putstr("File name missing.\n");
		return (0);
	}
	ft_cat(argv[1]);
	return (0);
}
