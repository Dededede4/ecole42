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

typedef	struct 					s_line
{
	uint64_t		left;
	char			middle;
	char			*right;
	t_bool			is_64;
	t_bool			is_32;
	struct s_line	*next;
}								t_line;



t_line*	get_line_trololo(int nsyms, int symoff, int stroff, char *ptr, off_t size)
{
	int i;
	int y;
	char *stringtable;
	struct  nlist_64 *el;

	t_line			*line;
	t_line			*tmp;

	line = NULL;
	tmp = NULL;
	if (size < symoff)
		exit(50);
	el = (void*)ptr + symoff;
	stringtable =  ptr + stroff;

	i = 0;
	while (i < nsyms)
	{
		if (size < symoff + sizeof(struct  nlist_64) * (i + 1))
			exit(51);
		if (size < stroff + el[i].n_un.n_strx + 1)
			exit(56);
		char *tmp = stringtable + el[i].n_un.n_strx;
		y = 0;
		if ((void*)tmp >= (void*)ptr + size)
			exit(58);
		while (tmp[y])
		{
			if (tmp + y + 1 >= ptr + size)
				exit(57);
			y++;
		}
		i++;
	}
	return (line);
}

t_line*	get_line_trololo_32(int nsyms, int symoff, int stroff, char *ptr, off_t size)
{
	int i;
	char *stringtable;
	struct  nlist *el;

	t_line			*line;
	t_line			*tmp;

	line = NULL;
	tmp = NULL;
	if (size < symoff)
		exit(50);
	el = (void*)ptr + symoff;
	stringtable =  ptr + stroff;

	i = 0;
	while (i < nsyms)
	{
		if (size < symoff + sizeof(struct  nlist) * (i + 1))
			exit(51);
		if (size < stroff + el[i].n_un.n_strx + 1)
			exit(57);
		i++;
	}
	return (line);
}



void handle_64_trololo(char * ptr, off_t size)
{
	int ncmds;
	struct mach_header_64 * header;
	struct load_command *lc;
	struct symtab_command *sym;

	int i = 0;
	int y = 0;
	int ycount = 1;

	struct section_64			*sec;
	t_list	*tmp;
	t_line			*line;

	header = (struct mach_header_64 *)ptr;
	ncmds  = header->ncmds;
	if (size < sizeof(*header) + sizeof(struct load_command))
		exit(46);
	lc = (void *)ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			if (size < (((void*)lc) - ((void*)ptr)) + sizeof(struct load_command))
				exit(47);
			sym = (struct symtab_command *)lc;
			line = get_line_trololo(sym->nsyms, sym->symoff, sym->stroff, ptr,  size);
			return ;
		}
		else if (lc->cmd == LC_SEGMENT_64)
		{
			if (size < (((void*)lc) - ((void*)ptr)) + sizeof(struct segment_command_64))
				exit(48);
			sec = (((void*)lc) + sizeof(struct segment_command_64));
			y = 0;
			while (y < ((struct segment_command_64 *)(lc))->nsects)
			{
				if (size < (((void*)sec) - ((void*)ptr)) + sizeof(struct section_64))
					exit(48);
				(sec) = (((void*)(sec)) + sizeof(struct section_64));
				y++;
				ycount++;
			}
		}
		if (size < (((void*)lc) - ((void*)ptr)) + lc->cmdsize)
		{
			exit(45);
		}
		lc = (void*) lc + lc ->cmdsize;
		i++;
	}
}


void handle_32_trololo(char * ptr, off_t size)
{
	int ncmds;
	struct mach_header * header;
	struct load_command *lc;
	struct symtab_command *sym;

	int i = 0;
	int y = 0;
	int ycount = 1;

	struct section			*sec;
	t_list	*tmp;
	t_line			*line;

	header = (struct mach_header *)ptr;
	ncmds  = header->ncmds;
	if (size < sizeof(*header) + sizeof(struct load_command))
		exit(46);
	lc = (void *)ptr + sizeof(*header);

	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			if (size < (((void*)lc) - ((void*)ptr)) + sizeof(struct load_command))
				exit(47);
			sym = (struct symtab_command *)lc;
			line = get_line_trololo_32(sym->nsyms, sym->symoff, sym->stroff, ptr,  size);
			return ;
		}
		else if (lc->cmd == LC_SEGMENT)
		{
			if (size < (((void*)lc) - ((void*)ptr)) + sizeof(struct segment_command))
				exit(48);
			sec = (((void*)lc) + sizeof(struct segment_command));
			y = 0;
			while (y < ((struct segment_command *)(lc))->nsects)
			{
				if (size < (((void*)sec) - ((void*)ptr)) + sizeof(struct section))
					exit(48);
				(sec) = (((void*)(sec)) + sizeof(struct section));
				y++;
				ycount++;
			}
		}
		if (size < (((void*)lc) - ((void*)ptr)) + lc->cmdsize)
			exit(45);
		lc = (void*) lc + lc ->cmdsize;
		i++;
	}
}

int antitroll(char *ptr, off_t size)
{
	int magic_number;

	struct fat_header *fat;
	struct fat_arch		*arch;
	uint32_t	i;
	char *cpy;

	if (size < sizeof (struct fat_header))
		exit(42);
	magic_number = *(int*) ptr;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64_trololo(ptr, size);
	}
	else if (magic_number == MH_MAGIC)
	{
		handle_32_trololo(ptr, size);
	}
	else if (magic_number == FAT_CIGAM) //  Universal Object
	{
		
		fat= (struct fat_header*)ptr;
		i = 0;
		if (size < sizeof (struct fat_header) + sizeof(struct fat_arch) * NXSwapLong(fat->nfat_arch))
				exit(43);
		while (i < NXSwapLong(fat->nfat_arch))
		{
			
			arch = (struct fat_arch*)(ptr + (sizeof(struct fat_header))) + i;
			if (NXSwapLong(arch->cputype) == CPU_TYPE_X86_64)
			{
				if (size < NXSwapLong(arch->offset) +  NXSwapLong(arch->size))
					exit(44);
				cpy = ft_memdup(ptr + NXSwapLong(arch->offset), NXSwapLong(arch->size));
				handle_64_trololo(cpy, NXSwapLong(arch->size));
				free(cpy);
			}
			/*else if (NXSwapLong(arch->cputype) == CPU_TYPE_I386)
			{

			}*/
			i++;
		}
	}
}

