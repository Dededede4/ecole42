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

void			display_for_files(t_params params)
{
	int		size;
	char	buf[64];
	int		old_size;


	while ((size = read(params.fd, buf, 64)) > 0)
	{
		if (params.p && params.fd == 0)
			write(1, buf, size);
		old_size = size;
		if (params.h == MD5)
			encrypt_md5(buf, size, &params);
		if (params.h == SHA256)
			encrypt_sha256(buf, size, &params);
	}
	if (old_size >= 56)
	{
		if (params.h == MD5)
			encrypt_md5(buf, 0, &params);
		if (params.h == SHA256)
			encrypt_sha256(buf, 0, &params);
	}
}

void			display_for_string(t_params params)
{
	uint64_t		size;
	uint64_t		rest;
	char	buf[64];
	uint64_t	old_size;
	uint64_t		i;

	size = ft_strlen(params.s);
	i = 0;
	while (i < size)
	{
		rest = (i + 64) < size ? 64 : size - i; 
		old_size = rest;
		if (params.h == MD5)
			encrypt_md5(params.s + i, rest, &params);
		if (params.h == SHA256)
			encrypt_sha256(params.s + i, rest, &params);
		i += 64;
	}
	if (old_size >= 56)
	{
		if (params.h == MD5)
			encrypt_md5(buf, 0, &params);
		if (params.h == SHA256)
			encrypt_sha256(buf, 0, &params);
	}
}

void			display_for_std(t_params params)
{
	params.fd = 0;
	display_for_files(params);
}


void			read_file(t_params params)
{
	if ((!params.s && !params.fn) || params.p)
	{
		display_for_std(params);
		ft_putchar('\n');
	}

	if (params.s)
	{
		if (params.h == MD5 && FALSE == params.q)
			ft_printf("MD5 (\"%s\") = ", params.s);
		if (params.h == SHA256 && FALSE == params.q)
			ft_printf("SHA256 (\"%s\") = ", params.s);
		display_for_string(params);
		ft_putchar('\n');
	}

	if (params.fn)
	{
		if (params.h == MD5 && FALSE == params.q)
			ft_printf("MD5 (%s) = ", params.fn);
		if (params.h == SHA256 && FALSE == params.q)
			ft_printf("SHA256 (%s) = ", params.fn);
		display_for_files(params);
		ft_putchar('\n');
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
