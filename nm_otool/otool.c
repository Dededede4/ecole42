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

#include "otool.h"

void	print_data(
	void *start, uint64_t size, uint64_t offset, t_command command)
{
	uint32_t		i;

	i = 0;
	while (i < size)
	{
		if (i % 16 == 0)
			ft_printf((command.is_64) ? "%016llx\t" : "%08llx\t", (offset) + i);
		if (!command.is_64 && command.header_32->cputype == CPU_TYPE_ARM)
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

void	nm(t_command command)
{
	command.magic_number = *(int*)(command.ptr);
	if (command.magic_number == MH_MAGIC_64)
		handle_64(command);
	else if (command.magic_number == MH_MAGIC)
		handle_32(command);
	else if (command.magic_number == FAT_CIGAM)
		handle_fat(command);
	else
		ft_printf("This magic number « %x » is unknow.\n",
			command.magic_number);
}

int		main(int ac, char **av)
{
	t_command	command;
	int			i;

	i = 1;
	if (ac <= 1)
		return (ft_printf("Please give me an arg\n"));
	while (i < ac)
	{
		command.path = av[i];
		if ((command.fd = open(av[i], O_RDONLY)) < 0)
			return (ft_printf("Error in open\n"));
		if (fstat(command.fd, &(command.buf)) < 0)
			return (ft_printf("Error in fstat\n"));
		if ((command.ptr = mmap(0, command.buf.st_size,
			PROT_READ, MAP_PRIVATE, command.fd, 0)) == MAP_FAILED)
			return (0);
		antitroll(command.ptr, command.buf.st_size);
		nm(command);
		ft_bzero(&command, sizeof(command));
		i++;
	}
	exit(0);
	return (0);
}
