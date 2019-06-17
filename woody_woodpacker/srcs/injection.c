#include "woody.h"

static void	replace_value(unsigned char *map, int64_t const size,
			      uint64_t searched, uint64_t value)
{
	int64_t	i;
	int64_t stop;
	int	founded;

	i = 0;
	founded = 0;
	stop = size - sizeof(uint64_t);
	while (i < stop) {
		if (*((uint64_t*)map) == searched) {
			if (searched == 0x4141414141414141)
				*((uint64_t*)map) = (i + value);
			else
				*((uint64_t*)map) = (value);
			founded++;
		}
		map++;
		i++;
	}
}

int			inject_code(Elf64_Ehdr *map, int maxaddr, int maxoff,
				    uint64_t size_encrypted, uint64_t secret)
{
	int		retval;

	*((char *)((void *)map + maxoff + VIRUS_SIZE)) = 0xe9;
	*((int *)((void *)map + maxoff + VIRUS_SIZE + 1)) = map->e_entry - (maxaddr + 5 + VIRUS_SIZE);
	replace_value(virus, VIRUS_SIZE, 0x4141414141414141, size_encrypted); // Offset start
	replace_value(virus, VIRUS_SIZE, 0x4343434343434342, size_encrypted); // Longueur à déchiffrer
	replace_value(virus, VIRUS_SIZE, 0x4444444444444444, secret); // la clef de déchiffrement

	ft_memcpy((void *)map + maxoff, virus, VIRUS_SIZE);

	map->e_entry = maxaddr;

	retval = 0;
	return retval;
}
