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

unsigned int ft_nxswaplong(unsigned int nbr);


void ifexit(t_bool cond, int nbr)
{
	if (cond)
		exit(nbr);
}

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
	ifexit((size < symoff), 50);
	el = (void*)ptr + symoff;
	stringtable =  ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		ifexit((size < symoff + (off_t)sizeof(struct  nlist_64) * (i + 1)), 51);
		ifexit((size < stroff + el[i].n_un.n_strx + 1), 56);
		char *tmp = stringtable + el[i].n_un.n_strx;
		y = 0;
		ifexit(((void*)tmp >= (void*)ptr + size), 58);
		while (tmp[y])
			ifexit((tmp + (++y) + 1 >= ptr + size), 57);
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
		if (size < symoff + (off_t)sizeof(struct  nlist) * (i + 1))
			exit(51);
		if (size < stroff + el[i].n_un.n_strx + 1)
			exit(57);
		i++;
	}
	return (line);
}

void handle_64_trololo_segment(void *ptr, off_t size, void *lc, int *ycount)
{
	struct section_64			*sec;
	uint32_t y = 0;

	ifexit((size < lc - ptr + (off_t)sizeof(struct segment_command_64)), 48);
	sec = (lc + sizeof(struct segment_command_64));
	y = 0;
	while (y < ((struct segment_command_64 *)(lc))->nsects)
	{
		ifexit((size < (((void*)sec) - ptr) + (off_t)sizeof(struct section_64)), 48);
		(sec) = (((void*)(sec)) + sizeof(struct section_64));
		y++;
		(*ycount)++;
	}
}

void handle_64_trololo(char * ptr, off_t size)
{
	struct mach_header_64 * header;
	struct load_command *lc;
	struct symtab_command *sym;
	uint32_t i = 0;
	int ycount = 1;

	ifexit((size < (off_t)sizeof(struct mach_header_64) + (off_t)sizeof(struct load_command)), 46);
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			ifexit((size < (((void*)lc) - ((void*)ptr)) + (off_t)sizeof(struct load_command)), 47);
			sym = (struct symtab_command *)lc;
			get_line_trololo(sym->nsyms, sym->symoff, sym->stroff, ptr,  size);
			return ;
		}
		else if (lc->cmd == LC_SEGMENT_64)
			handle_64_trololo_segment(ptr, size, lc, &ycount);
		ifexit((size < (((void*)lc) - ((void*)ptr)) + lc->cmdsize), 45);
		lc = (void*) lc + lc ->cmdsize;
		i++;
	}
}


void handle_32_trololo_segment(void *ptr, off_t size, void *lc, int *ycount)
{
	struct section			*sec;
	uint32_t y;

	ifexit((size < lc - ptr + (off_t)sizeof(struct segment_command)), 48);
	sec = (lc + sizeof(struct segment_command));
	y = 0;
	while (y < ((struct segment_command *)(lc))->nsects)
	{
		ifexit((size < (((void*)sec) - ptr) + (off_t)sizeof(struct section)), 48);
		(sec) = (((void*)(sec)) + sizeof(struct section));
		y++;
		(*ycount)++;
	}
}

void handle_32_trololo(char * ptr, off_t size)
{
	struct mach_header * header;
	struct load_command *lc;
	struct symtab_command *sym;
	uint32_t i = 0;
	int ycount = 1;

	ifexit((size < (off_t)sizeof(struct mach_header) + (off_t)sizeof(struct load_command)), 46);
	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			ifexit((size < (((void*)lc) - ((void*)ptr)) + (off_t)sizeof(struct load_command)), 47);
			sym = (struct symtab_command *)lc;
			get_line_trololo_32(sym->nsyms, sym->symoff, sym->stroff, ptr,  size);
			return ;
		}
		else if (lc->cmd == LC_SEGMENT)
			handle_32_trololo_segment(ptr, size, lc, &ycount);
		ifexit((size < (((void*)lc) - ((void*)ptr)) + lc->cmdsize), 45);
		lc = (void*) lc + lc ->cmdsize;
		i++;
	}
}

void handle_fat_trololo(char *ptr, off_t size)
{
	uint32_t	i;
	char		*cpy;
	struct fat_header *fat;
	struct fat_arch		*arch;

	fat = (struct fat_header*)ptr;
	i = 0;
	ifexit((size < (off_t)sizeof (struct fat_header) + (off_t)sizeof(struct fat_arch) * ft_nxswaplong(fat->nfat_arch)), 43);
	while (i < ft_nxswaplong(fat->nfat_arch))
	{
		arch = (struct fat_arch*)(ptr + (sizeof(struct fat_header))) + i;
		if (ft_nxswaplong(arch->cputype) == CPU_TYPE_X86_64)
		{
			ifexit((size < ft_nxswaplong(arch->offset) +  ft_nxswaplong(arch->size)), 44);
			cpy = ft_memdup(ptr + ft_nxswaplong(arch->offset), ft_nxswaplong(arch->size));
			handle_64_trololo(cpy, ft_nxswaplong(arch->size));
			free(cpy);
		}
		i++;
	}	
}

void antitroll(char *ptr, off_t size)
{
	unsigned int magic_number;

	ifexit((size < (off_t)sizeof(struct fat_header)),  42);
	magic_number = *(int*) ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64_trololo(ptr, size);
	else if (magic_number == MH_MAGIC)
		handle_32_trololo(ptr, size);
	else if (magic_number == FAT_CIGAM)
		handle_fat_trololo(ptr, size);
}

unsigned int ft_nxswaplong(unsigned int nbr)
{
	unsigned int result;
	char *sub_result;
	char *sub_nbr;

	sub_nbr = (char *)&nbr;
	sub_result = (char *)&result;
	sub_result[0] = sub_nbr[3];
	sub_result[1] = sub_nbr[2];
	sub_result[2] = sub_nbr[1];
	sub_result[3] = sub_nbr[0];
	return (result);
}

