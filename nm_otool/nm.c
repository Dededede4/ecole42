#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"

void	print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int i;
	char *stringtable;
	struct  nlist_64 *el;

	el = (void*)ptr + symoff;
	stringtable =  ptr + stroff;

	while (i < nsyms)
	{
		if (el[i].n_type == N_UNDF)
			ft_printf("U");
		else
			ft_printf("? -> %d <-", el[i].n_type);
		ft_printf("%s\n", stringtable + el[i].n_un.n_strx);
		i++;
	}
}

void handle_64(char * ptr)
{
	int ncmds;
	struct mach_header_64 * header;
	struct load_command *lc;
	struct symtab_command *sym;

	int i = 0;

	header = (struct mach_header_64 *)ptr;
	ncmds  = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			//ft_printf("nb symboles : %d\n", sym->nsyms);
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		lc = (void*) lc + lc ->cmdsize;
		i++;
	}


}

void nm(char *ptr)
{
	int magic_number;

	magic_number = *(int*) ptr;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
	}

}

int main(int ac, char **av)
{
	int		fd;
	char	*ptr;
	struct stat	buf;

	if (ac != 2)
	{
		ft_printf("Please give me an arg\n");
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_printf("Erreur dans open");
		return (0);
	}
	if (fstat(fd, &buf) < 0)
	{
		ft_printf("fstat");
		return (0);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("mmap");
		return (0);
	}
	nm(ptr);
	/*if (munmap(ptr, buf.st_size < 0))
	{
		ft_printf("munmap");
		return (0);
	}*/
	return (EXIT_SUCCESS);
}
