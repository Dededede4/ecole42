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

#define MD5 1
#define SHA256 2

int				print_usage(void)
{
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}

int				print_error(void)
{
	ft_printf("Standard commands:\n\nMessage Digest commands:\n\
md5\n\
sha256\n\
\n\
Cipher commands:\n");
	return (1);
}

void			sub_get_params(t_params *params, int argc, char **argv)
{
	int			i;

	i = 2;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-p"))
			params->p = TRUE;
		else if (ft_strequ(argv[i], "-q"))
			params->q = TRUE;
		else if (ft_strequ(argv[i], "-r"))
			params->r = TRUE;
		else if (ft_strequ(argv[i], "-s") && (i + 1) < argc)
			params->s = argv[++i];
		else if ((params->error = TRUE))
			print_error();
		i++;
	}
}

t_params		get_params(int argc, char **argv)
{
	t_params	params;

	ft_bzero(&params, sizeof(params));
	if (ft_strequ(argv[1], "md5"))
		params.h = MD5;
	else if (ft_strequ(argv[1], "sha256"))
		params.h = SHA256;
	else if ((params.error = TRUE))
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", argv[1]);
		print_error();
	}
	sub_get_params(&params, argc, argv);
	return (params);
}

int				main(int argc, char **argv)
{
	t_params	params;

	if (argc <= 1)
		return (print_usage());
	params = get_params(argc, argv);
	(void)params;
	return (0);
}
