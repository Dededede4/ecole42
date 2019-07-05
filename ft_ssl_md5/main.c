/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:08:34 by mprevot           #+#    #+#             */
/*   Updated: 2019/07/02 16:08:36 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int				print_usage(void)
{
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}

int				main(int argc, char **argv)
{
	t_params	params;

	if (argc <= 1)
		return (print_usage());
	params = get_params(argc, argv);
	if (params.error)
		return (0);
	read_file(params);
	return (0);
}
