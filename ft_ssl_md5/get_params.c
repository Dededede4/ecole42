/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:02:54 by mprevot           #+#    #+#             */
/*   Updated: 2019/07/02 19:02:55 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int				print_error(void)
{
	ft_printf("Standard commands:\n\nMessage Digest commands:\n\
md5\n\
sha256\n\
\n\
Cipher commands:\n");
	return (1);
}

void			sub_get_params_error(t_params *params, int i, char **argv)
{
	params->error = TRUE;
	if (params->h == MD5)
		ft_printf("ft_ssl: md5: %s: %s\n", argv[i], strerror(errno));
	else
		ft_printf("ft_ssl: sha256: %s: %s\n", argv[i], strerror(errno));
}

#define INIT_I int i = 2;

int				sub_get_params(t_params *params, int argc, char **argv)
{
	INIT_I;
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
		else if ((i + 1) == argc)
		{
			if ((params->fd = open(argv[i], O_RDONLY)) < 0)
				sub_get_params_error(params, i, argv);
		}
		else if ((params->error = TRUE))
			print_error();
		i++;
	}
	return (0);
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
