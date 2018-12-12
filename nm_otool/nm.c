#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"

int antitroll(char *ptr, off_t size);

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

char	get_type(struct nlist_64 el)
{
	t_bool upper;
	char 	c;

	upper = (0 != (el.n_type & N_EXT));

	if (0 != (el.n_type & N_STAB))
		c = '-';
	else if (N_UNDF == (el.n_type & N_TYPE))
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
	else if (el.n_desc & N_WEAK_REF)
		c = 'W';
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
		return (c);
	else
		return (ft_tolower(c));
}

char	get_type_32(struct nlist el)
{
	t_bool upper;
	char 	c;

	upper = (0 != (el.n_type & N_EXT));

	if (0 != (el.n_type & N_STAB))
		c = '-';
	else if (N_UNDF == (el.n_type & N_TYPE))
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
	else if (el.n_desc & N_WEAK_REF)
		c = 'W';
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
		return (c);
	else
		return (ft_tolower(c));
}

t_line*	get_line(int nsyms, int symoff, int stroff, char *ptr)
{
	int i;
	char *stringtable;
	struct  nlist_64 *el;

	t_line			*line;
	t_line			*tmp;

	line = NULL;
	tmp = NULL;
	el = (void*)ptr + symoff;
	stringtable =  ptr + stroff;

	i = 0;
	while (i < nsyms)
	{
		tmp = ft_memalloc(sizeof(*line));
		if (line)
			tmp->next = line;
		line = tmp;
		line->left = el[i].n_value;
		line->middle = get_type(el[i]);
		line->right = stringtable + el[i].n_un.n_strx;
		line->is_64 = TRUE;
		line->is_32 = FALSE;
		i++;
	}
	return (line);
}

t_line*	get_line_32(int nsyms, int symoff, int stroff, void *ptr)
{
	int i;
	char *stringtable;
	struct  nlist *el;

	t_line			*line;
	t_line			*tmp;

	line = NULL;
	tmp = NULL;
	el = (void*)ptr + symoff;
	stringtable =  ptr + stroff;

	i = 0;
	while (i < nsyms)
	{
		tmp = ft_memalloc(sizeof(*line));
		if (line)
			tmp->next = line;
		line = tmp;
		line->left = el[i].n_value;
		line->middle = get_type_32(el[i]);
		line->right = stringtable + el[i].n_un.n_strx;
		line->is_32 = TRUE;
		line->is_64 = FALSE;
		i++;
	}
	return (line);
}


void	tri_pourri_lol(t_line **first)
{
	t_line *line;
	t_line *tmp;
	t_line *before;

	line = *first;
	before = NULL;
	int diff;
	while(line->next)
	{
		diff = ft_strcmp(line->right, line->next->right);
		if(diff > 0 || 
			(diff == 0 && line->left > 0 && line->next->left == 0) ||
			(diff == 0 && line->left != 0 && line->next->left != 0 && line->left > line->next->left)
			)
		{
			if (before)
			{
				tmp = line->next->next;
				before->next = line->next;
				before->next->next = line;
				before->next->next->next = tmp;
			}
			else
			{
				tmp = line->next->next;
				*first = line->next;
				(*first)->next = line;
				(*first)->next->next = tmp;
			}
			line = *first;
			before = NULL;
			continue;
		}
		before = line;
		line = line->next;
	}
}

t_bool	can_show(t_line *first, t_line *findme)
{
	t_line	*line;
	int 	i;

	i = 0;
	line = first;
	
	if (0 == ft_strlen(findme->right) || findme->middle == '?' || findme->middle == '-')
		return FALSE;

	while (line)
	{
			if (0 == ft_strcmp(line->right, findme->right)
				&& line->middle == findme->middle
				&& (line->left == findme->left || !line->left || !findme->left))
			{
				if (line == findme)
					return TRUE;
				line = line->next;
				break;
			}
		line = line->next;
	}

	while (line)
	{
			if (0 == ft_strcmp(line->right, findme->right)
				&& line->middle == findme->middle
				&& (line->left == findme->left || !line->left || !findme->left))
			{
				return (FALSE);
			}
		line = line->next;
	}


	return TRUE;
}

void	print_line(t_line *line)
{
	t_line *first;

	first = line;
	while (line)
	{
		if (can_show(first, line))
		{
			if (line->is_64)
			{
				if(line->left || line->middle == 'T')
					ft_printf("%016llx ", line->left);
				else
					ft_printf("                 ");
			}
			if (line->is_32)
			{
				if(line->left || line->middle == 'T')
					ft_printf("%08llx ", line->left);
				else
					ft_printf("         ");
			}
			ft_putchar(line->middle);
			ft_printf( " %s\n", line->right);
		}
		line = line->next;
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
	t_line			*line;

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
			line = get_line(sym->nsyms, sym->symoff, sym->stroff, ptr);
			tri_pourri_lol(&line);
			print_line(line);
			exit(0);
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
				else if ( ft_strequ((sec_64)->sectname, "__data"))
				{
					tmp = ft_lstnew(&ycount, 4);
					if (command.data_numbers)
						tmp->next = command.data_numbers;
					command.data_numbers = tmp;
				}
				else if (ft_strequ((sec_64)->sectname, "__text"))
				{
					tmp = ft_lstnew(&ycount, 4);
					if (command.text_numbers)
						tmp->next = command.text_numbers;
					command.text_numbers = tmp;
				}
				else
				{
					tmp = ft_lstnew(&ycount, 4);
					if (command.const_numbers)
						tmp->next = command.const_numbers;
					command.const_numbers = tmp;
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


void handle_32(char * ptr)
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
	lc = (void *)ptr + sizeof(*header);

	while (i < ncmds)
	{
		//ft_printf(">>>>%d<<<< \n", i);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			//˛("nb symboles : %d\n", sym->nsyms);
			line = get_line_32(sym->nsyms, sym->symoff, sym->stroff, ptr);
			tri_pourri_lol(&line);
			print_line(line);
			exit(0);
		}
		else if (lc->cmd == LC_SEGMENT)
		{
			sec = (((void*)lc) + sizeof(struct segment_command));
			y = 0;
			while (y < ((struct segment_command *)(lc))->nsects)
			{
				//ft_printf("__ >> %s << __\n", (sec)->sectname);
				if (ft_strequ((sec)->sectname, "__bss"))
				{
					tmp = ft_lstnew(&ycount, 4);
					if (command.bss_numbers)
						tmp->next = command.bss_numbers;
					command.bss_numbers = tmp;
				}
				else if ( ft_strequ((sec)->sectname, "__data"))
				{
					tmp = ft_lstnew(&ycount, 4);
					if (command.data_numbers)
						tmp->next = command.data_numbers;
					command.data_numbers = tmp;
				}
				else if (ft_strequ((sec)->sectname, "__text"))
				{
					tmp = ft_lstnew(&ycount, 4);
					if (command.text_numbers)
						tmp->next = command.text_numbers;
					command.text_numbers = tmp;
				}
				else if (ft_strequ((sec)->sectname, "__text"))
				{
					tmp = ft_lstnew(&ycount, 4);
					if (command.text_numbers)
						tmp->next = command.text_numbers;
					command.text_numbers = tmp;
				}
				else
				{
					tmp = ft_lstnew(&ycount, 4);
					if (command.const_numbers)
						tmp->next = command.const_numbers;
					command.const_numbers = tmp;
				}
				// __text
				// 
				(sec) = (((void*)(sec)) + sizeof(struct section));
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
		handle_32(ptr);
	}
	else if (magic_number == FAT_CIGAM) //  Universal Object
	{
		fat= (struct fat_header*)ptr;
		i = 0;
		while (i < NXSwapLong(fat->nfat_arch))
		{
			arch = (struct fat_arch*)(ptr + (sizeof(struct fat_header))) + i;
			if (NXSwapLong(arch->cputype) == CPU_TYPE_X86_64)
			{
				cpy = ft_memdup(ptr + NXSwapLong(arch->offset), NXSwapLong(arch->size));
				handle_64(cpy);
				free(cpy);
			}
			else if (NXSwapLong(arch->cputype) == CPU_TYPE_I386)
			{

			}
			else
			{
				// ft_printf("This CPUType « %x » is unknow.\n", NXSwapLong(arch->cputype));
			}
			i++;
		}
	}
	else
	{
		// ft_printf("This magic number « %x » is unknow.\n", magic_number);
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
		return (0);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		return (0);
	}
	antitroll(ptr, buf.st_size);
	nm(ptr);
	/*if (munmap(ptr, buf.st_size < 0))
	{
		ft_printf("munmap");
		return (0);
	}*/
	return (EXIT_SUCCESS);
}
