/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:04:45 by mprevot           #+#    #+#             */
/*   Updated: 2019/07/05 15:04:46 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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
	char			buf[64];
	uint64_t		old_size;
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

void			read_before_file(t_params params)
{
	if ((!params.s && 0 == params.nfn) || params.p)
	{
		display_for_std(params);
		ft_putchar('\n');
	}
	if (params.s)
	{
		if (FALSE == params.r && params.h == MD5 && FALSE == params.q)
			ft_printf("MD5 (\"%s\") = ", params.s);
		if (FALSE == params.r && params.h == SHA256 && FALSE == params.q)
			ft_printf("SHA256 (\"%s\") = ", params.s);
		display_for_string(params);
		if (TRUE == params.r && params.h == MD5 && FALSE == params.q)
			ft_printf(" \"%s\"", params.s);
		if (TRUE == params.r && params.h == SHA256 && FALSE == params.q)
			ft_printf(" \"%s\"", params.s);
		ft_putchar('\n');
	}
}

void			read_file(t_params params)
{
	int i;

	i = 0;
	read_before_file(params);
	while (i < params.nfn)
	{
		params.fn = params.fns[i];
		if ((params.fd = open(params.fn, O_RDONLY)) < 0)
			sub_get_params_error(&params, params.fn);
		else
		{
			if (FALSE == params.r && params.h == MD5 && FALSE == params.q)
				ft_printf("MD5 (%s) = ", params.fn);
			if (FALSE == params.r && params.h == SHA256 && FALSE == params.q)
				ft_printf("SHA256 (%s) = ", params.fn);
			display_for_files(params);
			if (TRUE == params.r && params.h == MD5 && FALSE == params.q)
				ft_printf(" %s", params.fn);
			if (TRUE == params.r && params.h == SHA256 && FALSE == params.q)
				ft_printf(" %s", params.fn);
			ft_putchar('\n');
		}
		i++;
	}
}
