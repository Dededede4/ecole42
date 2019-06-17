/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 13:07:54 by heynard           #+#    #+#             */
/*   Updated: 2019/05/15 18:03:06 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

int		main(int argc, char **argv)
{
	int64_t	size;
	int		fd;
	char		*map;
	unsigned char secret[8];

	if (argc != 2) {
		dprintf(STDERR_FILENO, "Error: Invalid number of arguments\n");
		dprintf(STDERR_FILENO, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	if (gen_secret(secret) < 0) {
		dprintf(STDERR_FILENO, "Error: unable to generate random key\n");
		return 1;
	}
	fd = open_file(argv[1], &size, O_RDONLY);
	if (fd < 0)
		return 1;

	map = (char *)mmap(0, size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED) {
		perror("mmap");
		return (1);
	}
	if (packer((Elf64_Ehdr *)map, size, secret) < 0)
		return -1;
	return dump_woody(map, fd, size);
}
