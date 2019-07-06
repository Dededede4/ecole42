/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:14:04 by mprevot           #+#    #+#             */
/*   Updated: 2019/07/02 16:14:08 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/libft.h"
# include <errno.h>

# define MD5 1
# define SHA256 2

typedef struct			s_params
{
	uint32_t			h;
	t_bool				p;
	t_bool				r;
	t_bool				q;
	t_bool				error;
	t_bool				is_last;
	char				*s;
	char				**fns;
	char				*fn;
	int					nfn;
	int					fd;
	char				*d;
	uint64_t			ds;
	uint32_t			h0;
	uint32_t			h1;
	uint32_t			h2;
	uint32_t			h3;
	uint32_t			h4;
	uint32_t			h5;
	uint32_t			h6;
	uint32_t			h7;
}						t_params;

# define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
# define RIGHTROTATE(x, c) (((x) >> (c)) | ((x) << (32 - (c))))

uint64_t				swap_uint64(uint64_t val);
t_params				get_params(int argc, char **argv);
int						encrypt_md5(
	char *data, uint64_t size, t_params *params);
int						encrypt_sha256(
	char *data, uint64_t size, t_params *params);
uint32_t				swap_uint32(uint32_t val);
void					get_file(t_params *params);
void					sub_get_params_error(
	t_params *params, char *name);
void					read_file(t_params params);
uint32_t				func_f(uint32_t x, uint32_t y, uint32_t z);
uint32_t				func_g(uint32_t x, uint32_t y, uint32_t z);
uint32_t				func_h(uint32_t x, uint32_t y, uint32_t z);
uint32_t				func_i(uint32_t x, uint32_t y, uint32_t z);
uint32_t				ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t				maj(uint32_t x, uint32_t y, uint32_t z);

#endif
