#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct					s_command
{
	uint32_t					bss_number;
	uint32_t					const_number;
	uint32_t					data_number;
	uint32_t					text_number;
}								t_command;

t_command command;

void	print_type(uint8_t type)
{
	ft_printf("  %b  ", type);
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

	i = 0;
	while (i < nsyms)
	{
		if(el[i].n_value)
			ft_printf("%016llx\t", el[i].n_value);
		if (command.bss_number == el[i].n_sect)
			ft_printf("BB");
		else if (command.const_number == el[i].n_sect)
			ft_printf("SS");
		else if (command.data_number == el[i].n_sect)
			ft_printf("DD");
		else if (command.text_number == el[i].n_sect)
			ft_printf("TT");
		else
			print_type(el[i].n_type);
		ft_printf( " ( %u %u )\t%s\n", el[i].n_sect, command.bss_number, stringtable + el[i].n_un.n_strx);
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
	int y = 0;
	int ycount = 1;

	struct section_64			*sec_64;

	header = (struct mach_header_64 *)ptr;
	ncmds  = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	
	while (i < ncmds)
	{
		//ft_printf(">>>>%d<<<< \n", i);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			//˛("nb symboles : %d\n", sym->nsyms);
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
		}
		else if (lc->cmd == LC_SEGMENT_64)
		{
			//ft_printf("__ %s __\n",((struct segment_command_64 *)(lc))->segname);
			sec_64 = (((void*)lc) + sizeof(struct segment_command_64));
			y = 0;
			while (y < ((struct segment_command_64 *)(lc))->nsects)
			{
				//ft_printf("__ >> %s << __\n", (sec_64)->sectname);
				if (command.bss_number == 0 && ft_strequ((sec_64)->sectname, "__bss"))
				{
					command.bss_number = ycount;
				}
				if (command.const_number == 0 && ft_strequ((sec_64)->sectname, "__const"))
				{
					command.const_number = ycount;
				}
				if (command.data_number == 0 && ft_strequ((sec_64)->sectname, "__data"))
				{
					command.data_number = ycount;
				}
				if (command.text_number == 0 && ft_strequ((sec_64)->sectname, "__text"))
				{
					command.text_number = ycount;
				}
				// __text
				// 
				(sec_64) = (((void*)(sec_64)) + sizeof(struct section_64));
				y++;
				ycount++;
			}
		}
		lc = (void*) lc + lc ->cmdsize;
		i++;
	}


}

void nm(char *ptr)
{
	command.bss_number = 0;
	command.const_number = 0;
	command.data_number = 0;
	command.text_number = 0;

	int magic_number;

	struct fat_header *fat;
	struct fat_arch		*arch;
	uint32_t	i;
	char *cpy;

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
				cpy = ft_memdup(ptr + NXSwapLong(arch->offset), NXSwapLong(arch->size));
				handle_64(cpy);
				free(cpy);
			}
			/*else if (NXSwapLong(arch->cputype) == CPU_TYPE_I386)
			{

			}*/
			i++;
		}
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
