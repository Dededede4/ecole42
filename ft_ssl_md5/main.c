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


void			read_file(t_params params)
{
	int		size;
	char	buf[56];

	while ((size = read(params.fd, buf, 56)) > 0)
	{
		size--;
		if (params.h == MD5)
			encrypt_md5(buf, size);
		if (params.h == SHA256)
			encrypt_sha256(buf, size);
	}
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
