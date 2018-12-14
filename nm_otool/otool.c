/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:10:20 by mprevot           #+#    #+#             */
/*   Updated: 2018/11/25 17:10:21 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "otool.h"

#include <mach-o/fat.h>

int antitroll(char *ptr, off_t size);

void	print_data(void *start, uint64_t size, uint64_t offset, t_bool is_64, t_command command)
{
	uint32_t		i;

	i = 0;
	while (i < size)
	{
		if (i % 16 == 0)
				ft_printf((is_64) ? "%016llx\t" : "%08llx\t", (offset) + i);
		if (!is_64 && command.header_32->cputype == CPU_TYPE_ARM)
		{
			if (i % 4 == 0)
				ft_printf("%08x ", ((unsigned int*)start)[i / 4]);
			if ((i + 1) % 16 == 0 || i + 1 == size)
				ft_printf("\n");
		}
		else
		{
			ft_printf("%02x ", ((unsigned char*)start)[i]);
			if ((i + 1) % 16 == 0 || i + 1 == size)
				ft_printf("\n");
		}
		i++;
	}
}

void	handle_64_next(int * y, t_command command)
{
	(command.seg_64) = (struct segment_command_64 *)(command.lc);
	if (ft_strequ((command.seg_64)->segname, "__TEXT"))
	{
		(command.sec_64) = (((void*)(command.seg_64)) + sizeof(struct segment_command_64));
		while ((*y) < (command.seg_64)->nsects)
		{
			if (ft_strequ((command.sec_64)->sectname, "__text"))
			{
				ft_printf("%s:\nContents of (__TEXT,__text) section\n", command.path);
				print_data((command.ptr) + (command.sec_64)->offset, (command.sec_64)->size, (command.sec_64)->addr, TRUE, command);
			}
			(command.sec_64) = (((void*)(command.sec_64)) + sizeof(struct section_64));
			(*y)++;
		}
	}
}
void	handle_64(t_command command)
{
	int i;
	int y;

	i = 0;
	y = 0;
	(command.header_64) = (struct mach_header_64 *)(command.ptr);
	(command.ncmds) = (command.header_64)->ncmds;
	(command.lc) = (void *)(command.ptr) + sizeof(*(command.header_64));
	while (i < (command.ncmds))
	{
		if ((command.lc)->cmd == LC_SEGMENT_64)
			handle_64_next(&y, command);
		(command.lc) = (void*) (command.lc) + (command.lc) ->cmdsize;
		i++;
	}
}

void	handle_32_next(int *y, t_command command)
{
	(command.seg_32) = (struct segment_command *)(command.lc);
	if (ft_strequ((command.seg_32)->segname, "__TEXT"))
	{
		(command.sec_32) = (((void*)(command.seg_32)) + sizeof(struct segment_command));
		while ((*y) < (command.seg_32)->nsects)
		{
			if (ft_strequ((command.sec_32)->sectname, "__text"))
			{
				ft_printf("%s:\nContents of (__TEXT,__text) section\n", command.path);
				print_data((command.ptr) + (command.sec_32)->offset, (command.sec_32)->size, (command.sec_32)->addr, FALSE, command);
			}
			(command.sec_32) = (((void*)(command.sec_32)) + sizeof(struct section));
			(*y)++;
		}
	}
}

void	handle_32(t_command command)
{
	int i;
	int y;

	i = 0;
	y = 0;
	(command.header_32) = (struct mach_header *)(command.ptr);
	(command.ncmds) = (command.header_32)->ncmds;
	(command.lc) = (void *)(command.ptr) + sizeof(*(command.header_32));
	while (i < (command.ncmds))
	{
		if ((command.lc)->cmd == LC_SEGMENT)
			handle_32_next(&y, command);
		(command.lc) = (void*) (command.lc) + (command.lc) ->cmdsize;
		i++;
	}
}

void handle_fat(t_command command)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			i;
	char				*cpy;
	void				*tmp;

	fat = (struct fat_header*)command.ptr;
	i = 0;
	while (i < NXSwapLong(fat->nfat_arch))
	{
		arch = (struct fat_arch*)(command.ptr + (sizeof(struct fat_header))) + i;
		if (NXSwapLong(arch->cputype) == CPU_TYPE_X86_64)
		{
			cpy = ft_memdup(command.ptr + NXSwapLong(arch->offset), NXSwapLong(arch->size));
			tmp = command.ptr;
			command.ptr = cpy;
			handle_64(command);
			free(cpy);
			command.ptr = tmp;
			break;
		}
		i++;
	}
}

void	nm(t_command command)
{
	command.magic_number = *(int*) (command.ptr);
	if (command.magic_number == MH_MAGIC_64)
		handle_64(command);
	else if (command.magic_number == MH_MAGIC)
		handle_32(command);
	else if (command.magic_number == FAT_CIGAM)
		handle_fat(command);
	else
		ft_printf("This magic number « %x » is unknow.\n", command.magic_number);
}


int		main(int ac, char **av)
{
	t_command	command;
	int			i;

	i = 1;
	if (ac <= 1)
		return ft_printf("Please give me an arg\n");
	while ( i < ac )
	{
		command.path = av[i];
		if ((command.fd = open(av[i], O_RDONLY)) < 0)
			return ft_printf("Error in open\n");
		if (fstat(command.fd, &(command.buf)) < 0)
			return ft_printf("Error in fstat\n");
		if ((command.ptr = mmap(0, command.buf.st_size, PROT_READ, MAP_PRIVATE, command.fd, 0)) == MAP_FAILED)
		{
			return (0);
		}
		antitroll(command.ptr, command.buf.st_size);
		nm(command);
		ft_bzero(&command, sizeof(command));
		i++;
	}
	exit(0);
	return (0);
}
