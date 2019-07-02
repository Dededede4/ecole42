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
	char		 		*s;
	int					fd;
}						t_params;

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
int encrypt_md5(char *data, uint64_t size);

int encrypt_sha256(char *data, uint64_t size);

uint32_t swap_uint32( uint32_t val );