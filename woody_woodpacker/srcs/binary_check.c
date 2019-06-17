#include "woody.h"

int	check_file_ident(Elf64_Ehdr *map, int64_t const size)
{
	if (map->e_ident[EI_MAG0] == ELFMAG0
	 && map->e_ident[EI_MAG1] == ELFMAG1
	 && map->e_ident[EI_MAG2] == ELFMAG2
	 && map->e_ident[EI_MAG3] == ELFMAG3
	 && map->e_ident[EI_CLASS] == ELFCLASS64) {
		if (map->e_ehsize + (map->e_phentsize * map->e_phnum)
		 + (map->e_shentsize * map->e_shnum < size))
			return 0;
	}
	dprintf(STDERR_FILENO, "Error: invalid file format\n");
	return -1;
}

int	check_cave_len(char *cave)
{
	int	size;

	size = 0;
	while (cave[size] == 0)
		size++;
	return size;
}
