/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:47:22 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/14 17:47:24 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	nm(char *ptr)
{
	unsigned int	magic_number;
	struct fat_arch	*arch;
	uint32_t		i;
	char			*cpy;

	magic_number = *(int*)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_number == MH_MAGIC)
		handle_32(ptr);
	else if (magic_number == FAT_CIGAM)
	{
		i = 0;
		while (i < ft_nxswaplong(((struct fat_header*)ptr)->nfat_arch))
		{
			arch = (struct fat_arch*)(ptr + (sizeof(struct fat_header))) + i++;
			if (ft_nxswaplong(arch->cputype) == CPU_TYPE_X86_64)
			{
				cpy = ft_memdup(ptr +
					ft_nxswaplong(arch->offset), ft_nxswaplong(arch->size));
				handle_64(cpy);
				free(cpy);
			}
		}
	}
}

int		main(int ac, char **av)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if (ac > 1)
	{
		if ((fd = open(av[1], O_RDONLY)) < 0)
			exit(0);
	}
	else
	{
		if ((fd = open("a.out", O_RDONLY)) < 0)
			exit(0);
	}
	if (fstat(fd, &buf) < 0)
		exit(0);
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		exit(0);
	antitroll(ptr, buf.st_size);
	nm(ptr);
	exit(0);
}
