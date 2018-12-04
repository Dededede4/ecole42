#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"

void	print_type(uint8_t type)
{
	if (0 != (type & N_STAB))
		ft_printf("-");
	if (0 != (type & N_PEXT))
		ft_printf("private external symbol bit");
	if (0 != (type & N_EXT))
		ft_printf("Upercase : "); 



	if (N_UNDF == (type & N_TYPE))
		ft_printf("U"); // undefined, n_sect == NO_SECT
	if (N_ABS == (type & N_TYPE))
		ft_printf("A"); // absolute, n_sect == NO_SECT
	if (N_SECT == (type & N_TYPE))
		ft_printf("T"); // defined in section number n_sect
	// if (N_PBUD == (type & N_TYPE))
		// ft_printf("U"); // prebound undefined (defined in a dylib)
	if (N_INDR == (type & N_TYPE))
		ft_printf("I"); // inderct

	/*if (nlist.n_desc & N_WEAK_REF)
		ft_printf("W");*/
}

void	print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int i;
	char *stringtable;
	struct  nlist_64 *el;

	el = (void*)ptr + symoff;
	stringtable =  ptr + stroff;

	while (i < nsyms)
	{
		print_type(el[i].n_type);
		ft_printf("\t%s\n", stringtable + el[i].n_un.n_strx);
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
			//˛("nb symboles : %d\n", sym->nsyms);
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

	struct fat_header *fat;
	struct fat_arch		*arch;
	uint32_t	i;

	magic_number = *(int*) ptr;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
	}
	else if (magic_number == MH_MAGIC)
	{
		ft_printf("32 bites"); exit(0);
	}
	else if (magic_number == FAT_CIGAM) //  Universal Object
	{
		fat= (struct fat_header*)ptr;
		i = 0;
		if (2 != NXSwapLong(fat->nfat_arch))
			exit(0);
		while (i < NXSwapLong(fat->nfat_arch))
		{
			arch = (struct fat_arch*)(ptr + (sizeof(struct fat_header))) + i;
			if (NXSwapLong(arch->cputype) == CPU_TYPE_X86_64)
			{
				ft_printf("64 bites : ");
			}
			else if (NXSwapLong(arch->cputype) == CPU_TYPE_I386)
			{
				ft_printf("32 bites : ");
			}
			i++;
		}
		ft_printf("pouet"); exit(0);
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
