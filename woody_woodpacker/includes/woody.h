#ifndef WOODY_H
# define WOODY_H

# include <stdlib.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <elf.h>
# include <byteswap.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdint.h>

# include "../libft/includes/libft.h"

# define VIRUS_SIZE 151

extern unsigned char	virus[VIRUS_SIZE];

int	open_file(char const *name, int64_t *size, int const mod);
int	write_file(char const *map, int64_t const size);
int	dump_woody(void *map, int const fd, int64_t const size);

int	packer(Elf64_Ehdr *map, int64_t const size, unsigned char *secret);
int	check_file_ident(Elf64_Ehdr *map, int64_t const size);
int	check_cave_len(char *cave);

int 	gen_secret(unsigned char *secret);
void	encrypt_main(void *bin, size_t len, unsigned char *secret);

int	inject_code(Elf64_Ehdr *map, int maxaddr, int maxoff, uint64_t size_encrypted, uint64_t secret);

#endif
