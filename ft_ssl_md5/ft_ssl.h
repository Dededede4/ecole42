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

#include "libft/libft.h"
#include <errno.h>

#define MD5 1
#define SHA256 2

typedef struct			s_params
{
	uint32_t			h;
	t_bool				p;
	t_bool				r;
	t_bool				q;
	t_bool				error;
	t_bool				is_last;
	char		 		*s;
	char				*fn;
	int					fd;
	char				*d;
	uint64_t			ds;
	uint32_t			AA;
	uint32_t			BB;
	uint32_t			CC;
	uint32_t			DD;
	uint32_t			EE;
	uint32_t			FF;
	uint32_t			GG;
	uint32_t			HH;
}						t_params;

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

#define ENDIAN_SWAP_U64(val) (( \
    (((val) & 0x00000000000000ff) << 56) | \
    (((val) & 0x000000000000ff00) << 40) | \
    (((val) & 0x0000000000ff0000) << 24) | \
    (((val) & 0x00000000ff000000) <<  8) | \
    (((val) & 0x000000ff00000000) >>  8) | \
    (((val) & 0x0000ff0000000000) >> 24) | \
    (((val) & 0x00ff000000000000) >> 40) | \
    (((val) & 0xff00000000000000) >> 56)))

t_params		get_params(int argc, char **argv);
int encrypt_md5(char *data, uint64_t size, t_params *params);

int encrypt_sha256(char *data, uint64_t size, t_params *params);

uint32_t swap_uint32( uint32_t val );

void	get_file(t_params *params);



#endif
