/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:11:29 by mprevot           #+#    #+#             */
/*   Updated: 2018/11/25 17:12:19 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include <inttypes.h>
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <mach-o/fat.h>
# include "libft/libft.h"

typedef struct					s_command
{
	char						*path;
	int							fd;
	char						*ptr;
	struct stat					buf;
	unsigned int				magic_number;
	int							ncmds;
	struct load_command			*lc;
	struct symtab_command		*sym;
	struct mach_header_64		*header_64;
	struct segment_command_64	*seg_64;
	struct section_64			*sec_64;
	struct mach_header			*header_32;
	struct segment_command		*seg_32;
	struct section				*sec_32;
	t_bool						is_64;
}								t_command;

void							print_data(
	void *start, uint64_t size, uint64_t offset, t_command command);
int								antitroll(char *ptr, off_t size);
unsigned int					ft_nxswaplong(unsigned int nbr);
void							handle_64(t_command command);
void							handle_32(t_command command);
void							handle_fat(t_command command);

#endif
