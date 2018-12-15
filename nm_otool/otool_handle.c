/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 02:26:29 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/15 02:26:31 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	handle_64_next(uint32_t *y, t_command command)
{
	(command.seg_64) = (struct segment_command_64 *)(command.lc);
	if (ft_strequ((command.seg_64)->segname, "__TEXT"))
	{
		(command.sec_64) = (((void*)(command.seg_64))
			+ sizeof(struct segment_command_64));
		while ((*y) < (command.seg_64)->nsects)
		{
			if (ft_strequ((command.sec_64)->sectname, "__text"))
			{
				ft_printf("%s:\nContents of (__TEXT,__text) section\n",
					command.path);
				print_data((command.ptr) + (command.sec_64)->offset,
					(command.sec_64)->size,
					(command.sec_64)->addr, command);
			}
			(command.sec_64) = (((void*)(command.sec_64))
				+ sizeof(struct section_64));
			(*y)++;
		}
	}
}

void	handle_64(t_command command)
{
	int			i;
	uint32_t	y;

	command.is_64 = TRUE;
	i = 0;
	y = 0;
	(command.header_64) = (struct mach_header_64 *)(command.ptr);
	(command.ncmds) = (command.header_64)->ncmds;
	(command.lc) = (void *)(command.ptr) + sizeof(*(command.header_64));
	while (i < (command.ncmds))
	{
		if ((command.lc)->cmd == LC_SEGMENT_64)
			handle_64_next(&y, command);
		(command.lc) = (void*)(command.lc)
			+ (command.lc)->cmdsize;
		i++;
	}
}

void	handle_32_next(uint32_t *y, t_command command)
{
	(command.seg_32) = (struct segment_command *)(command.lc);
	if (ft_strequ((command.seg_32)->segname, "__TEXT"))
	{
		(command.sec_32) = (((void*)(command.seg_32))
			+ sizeof(struct segment_command));
		while ((*y) < (command.seg_32)->nsects)
		{
			if (ft_strequ((command.sec_32)->sectname, "__text"))
			{
				ft_printf("%s:\nContents of (__TEXT,__text) section\n",
					command.path);
				print_data((command.ptr) + (command.sec_32)->offset,
					(command.sec_32)->size,
					(command.sec_32)->addr, command);
			}
			(command.sec_32) = (((void*)(command.sec_32))
				+ sizeof(struct section));
			(*y)++;
		}
	}
}

void	handle_32(t_command command)
{
	int			i;
	uint32_t	y;

	command.is_64 = FALSE;
	i = 0;
	y = 0;
	(command.header_32) = (struct mach_header *)(command.ptr);
	(command.ncmds) = (command.header_32)->ncmds;
	(command.lc) = (void *)(command.ptr) + sizeof(*(command.header_32));
	while (i < (command.ncmds))
	{
		if ((command.lc)->cmd == LC_SEGMENT)
			handle_32_next(&y, command);
		(command.lc) = (void*)(command.lc) + (command.lc)->cmdsize;
		i++;
	}
}

void	handle_fat(t_command command)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			i;
	char				*cpy;
	void				*tmp;

	fat = (struct fat_header*)command.ptr;
	i = 0;
	while (i < ft_nxswaplong(fat->nfat_arch))
	{
		arch = (struct fat_arch*)(command.ptr +
			(sizeof(struct fat_header))) + i;
		if (ft_nxswaplong(arch->cputype) == CPU_TYPE_X86_64)
		{
			cpy = ft_memdup(command.ptr + ft_nxswaplong(arch->offset),
				ft_nxswaplong(arch->size));
			tmp = command.ptr;
			command.ptr = cpy;
			handle_64(command);
			free(cpy);
			command.ptr = tmp;
			break ;
		}
		i++;
	}
}
