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
	t_list						*bss_numbers;
	t_list						*const_numbers;
	t_list						*data_numbers;
	t_list						*text_numbers;

}								t_command;

t_command command;

/*static char	get_type(const uint64_t n_value, const uint8_t n_type, \
				const uint8_t n_sect, const uint16_t n_desc)
{
	const int	n_type_field = N_TYPE & n_type;
	char		type = '?';

	if (N_STAB & n_type)
		type = '-';
	else if (n_type_field == N_UNDF)
		type = n_value ? 'c' : 'u';
	else if (n_type_field == N_ABS)
		type = 'a';
	else if (n_type_field == N_SECT && \
		!(type = nm_sections_character_table(FIRST_BIT_ON_64 | n_sect)))
		type = '?';
	else if (n_type_field == N_PBUD)
		type = 'u';
	else if (n_type_field == N_INDR)
		type = 'i';
	else if (n_desc & N_WEAK_REF)
		type = 'W';

	//if external set uppercase
	if (N_EXT & n_type)
		type = ft_toupper(type);

	return (type);
}*/


t_bool 	lookfor(uint8_t n_sect, t_list *lst)
{
	while(lst)
	{

		if (*((int*)((lst->content))) == n_sect)
			return TRUE;
		lst = lst->next;
	}
	return FALSE;
}

void	print_type(struct nlist_64 el)
{
	t_bool upper;
	char 	c;

	upper = (0 != (el.n_type & N_EXT));

	if (0 != (el.n_type & N_STAB))
		c = '-';
	if (N_UNDF == (el.n_type & N_TYPE))
	{
		if (el.n_value)
			c = 'C'; // undefined, n_sect == NO_SECT
		else
			c = 'U';
	}
	else if (N_ABS == (el.n_type & N_TYPE))
		c = 'A'; // absolute, n_sect == NO_SECT
	else if (N_INDR == (el.n_type & N_TYPE))
		c = 'I'; // inderct
	else if (lookfor(el.n_sect, command.bss_numbers))
		c = 'B';
	else if (lookfor(el.n_sect, command.const_numbers))
		c = 'S';
	else if (lookfor(el.n_sect, command.data_numbers))
		c = 'D';
	else if (lookfor(el.n_sect, command.text_numbers))
		c = 'T';
	else
		c = '?';

	if (upper)
		ft_putchar(c);
	else
		ft_putchar(ft_tolower(c));



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
		if(el[i].n_value || lookfor(el[i].n_sect, command.text_numbers)) // T
			ft_printf("%016llx ", el[i].n_value);
		else
			ft_printf("                 ");
		print_type(el[i]);
		ft_printf( " %s\n", stringtable + el[i].n_un.n_strx);
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
	t_list	*tmp;

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
				if (ft_strequ((sec_64)->sectname, "__bss"))
				{
					tmp = ft_lstnew(&ycount, 4);
					if (command.bss_numbers)
						tmp->next = command.bss_numbers;
					command.bss_numbers = tmp;
				}
				if (ft_strequ((sec_64)->sectname, "__const"))
				{
					tmp = ft_lstnew(&ycount, 4);
					if (command.const_numbers)
						tmp->next = command.const_numbers;
					command.const_numbers = tmp;
				}
				if ( ft_strequ((sec_64)->sectname, "__data"))
				{
					tmp = ft_lstnew(&ycount, 4);
					if (command.data_numbers)
						tmp->next = command.data_numbers;
					command.data_numbers = tmp;
				}
				if (ft_strequ((sec_64)->sectname, "__text"))
				{
					tmp = ft_lstnew(&ycount, 4);
					if (command.text_numbers)
						tmp->next = command.text_numbers;
					command.text_numbers = tmp;
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
	command.const_numbers = NULL;
	command.data_numbers = NULL;
	command.text_numbers = NULL;
	command.bss_numbers = NULL;

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
