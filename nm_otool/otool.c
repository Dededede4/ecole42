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

void	print_data(void *start, uint64_t size, uint64_t offset)
{
	uint32_t		i;

	i = 0;
	while (i < size)
	{
		if (i % 16 == 0)
		{
			ft_printf("%016llx\t", (offset) + i);
		}
		ft_printf("%02x", ((unsigned char*)start)[i]);
		if ((i + 1) % 16 == 0 || i + 1 == size)
		{
			ft_printf(" \n");
		}
		else
		{
			ft_printf(" ");
		}
		i++;
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
		{
			(command.seg_64) = (struct segment_command_64 *)(command.lc);
			if (ft_strequ((command.seg_64)->segname, "__TEXT"))
			{
				(command.sec_64) = (((void*)(command.seg_64)) + sizeof(struct segment_command_64));
				while (y < (command.seg_64)->nsects)
				{
					if (ft_strequ((command.sec_64)->sectname, "__text"))
					{
						ft_printf("%s:\nContents of (__TEXT,__text) section\n", command.path);
						print_data((command.ptr) + (command.sec_64)->offset, (command.sec_64)->size, (command.sec_64)->addr);
					}
					
					(command.sec_64) = (((void*)(command.sec_64)) + sizeof(struct section_64));
					y++;
				}
			}
		}
		(command.lc) = (void*) (command.lc) + (command.lc) ->cmdsize;
		i++;
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
		{
			(command.seg_32) = (struct segment_command *)(command.lc);
			if (ft_strequ((command.seg_32)->segname, "__TEXT"))
			{
				(command.sec_32) = (((void*)(command.seg_32)) + sizeof(struct segment_command));
				while (y < (command.seg_32)->nsects)
				{
					if (ft_strequ((command.sec_32)->sectname, "__text"))
					{
						ft_printf("%s:\nContents of (__TEXT,__text) section\n", command.path);
						print_data((command.ptr) + (command.sec_32)->offset, (command.sec_32)->size, (command.sec_32)->offset);
					}
					
					(command.sec_32) = (((void*)(command.sec_32)) + sizeof(struct section));
					y++;
				}
			}
		}
		(command.lc) = (void*) (command.lc) + (command.lc) ->cmdsize;
		i++;
	}
}

void	nm(t_command command)
{
	command.magic_number = *(int*) (command.ptr);
	if (command.magic_number == MH_MAGIC_64)
	{
		handle_64(command);
	}
	else if (command.magic_number == MH_MAGIC)
	{
		handle_32(command);
	}
	else
	{
		ft_printf("This magic number « %x » is unknow.\n", command.magic_number);
	}
}



int		main(int ac, char **av)
{

	t_command	command;
	int			i;

	i = 1;
	if (ac <= 1)
	{
		ft_printf("Please give me an arg\n");
		return (0);
	}
	while ( i < ac )
	{
		command.path = av[i];
		if ((command.fd = open(av[i], O_RDONLY)) < 0)
		{
			ft_printf("Error in open\n");
			return (0);
		}
		if (fstat(command.fd, &(command.buf)) < 0)
		{
			ft_printf("Error in fstat\n");
			return (0);
		}
		if ((command.ptr = mmap(0, command.buf.st_size, PROT_READ, MAP_PRIVATE, command.fd, 0)) == MAP_FAILED)
		{
			ft_printf("Error in mmap\n");
			return (0);
		}
		nm(command);
		ft_bzero(&command, sizeof(command));
		i++;
	}
	return (0);
}
