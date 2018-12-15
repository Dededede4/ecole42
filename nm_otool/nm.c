/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:47:22 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/14 17:47:24 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"

int antitroll(char *ptr, off_t size);
unsigned int ft_nxswaplong(unsigned int nbr);

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


char	get_type_lookfor(uint8_t n_sect)
{
	char 	c;

	if (lookfor(n_sect, command.bss_numbers))
		c = 'B';
	else if (lookfor(n_sect, command.const_numbers))
		c = 'S';
	else if (lookfor(n_sect, command.data_numbers))
		c = 'D';
	else if (lookfor(n_sect, command.text_numbers))
		c = 'T';
	else
		c = '?';
	return (c);
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
	else
		c = get_type_lookfor(el.n_sect);
	if (upper)
		return (c);
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
	else
		c = get_type_lookfor(el.n_sect);
	if (upper)
		return (c);
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

void	tri_pourri_lol_switch(t_line *line, t_line *before, t_line **first)
{
	t_line *tmp;

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
}

void	tri_pourri_lol(t_line **first)
{
	t_line *line;
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
			tri_pourri_lol_switch(line, before, first);
			line = *first;
			before = NULL;
			continue;
		}
		before = line;
		line = line->next;
	}
}

t_bool	can_show_next(t_line *line, t_line *findme)
{
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
	return (TRUE);
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
	return can_show_next(line, findme);
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
			ft_printf("%C %s\n", line->middle, line->right);
		}
		line = line->next;
	}
}


void segname2struct_switch(int ycount, t_list **data)
{
	t_list *tmp;

	tmp = ft_lstnew(&ycount, 4);
	if (*data)
		tmp->next = *data;
	*data = tmp;
}

void segname2struct(int ycount, char * sectname)
{
	if (ft_strequ(sectname, "__bss"))
		segname2struct_switch(ycount, &(command.bss_numbers));
	else if (ft_strequ(sectname, "__data"))
		segname2struct_switch(ycount, &(command.data_numbers));
	else if (ft_strequ(sectname, "__text"))
		segname2struct_switch(ycount, &(command.text_numbers));
	else
		segname2struct_switch(ycount, &(command.const_numbers));
}

void handle_64_segment(void *lc, int *ycount)
{
	struct section_64			*sec_64;
	uint32_t y;

	sec_64 = (((void*)lc) + sizeof(struct segment_command_64));
	y = 0;
	while (y < ((struct segment_command_64 *)(lc))->nsects)
	{
		segname2struct(*ycount, sec_64->sectname);
		(sec_64) = (((void*)(sec_64)) + sizeof(struct section_64));
		y++;
		(*ycount)++;
	}
}

void handle_64(char * ptr)
{
	int ncmds;
	struct load_command *lc;
	int i;
	int ycount;	
	t_line	*line;

	ncmds  = ((struct mach_header_64*)ptr)->ncmds;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	i = 0;
	ycount = 1;
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			line = get_line(((struct symtab_command *)lc)->nsyms, 
				((struct symtab_command *)lc)->symoff,
				((struct symtab_command *)lc)->stroff, ptr);
			tri_pourri_lol(&line);
			print_line(line);
			exit(0);
		}
		else if (lc->cmd == LC_SEGMENT_64)
			handle_64_segment(lc, &ycount);
		lc = (void*) lc + lc ->cmdsize;
	}
}

void handle_32_segment(void *lc, int *ycount)
{
	struct section			*sec;
	uint32_t y;

	sec = (((void*)lc) + sizeof(struct segment_command));
	y = 0;
	while (y < ((struct segment_command *)(lc))->nsects)
	{
		segname2struct(*ycount, sec->sectname);
		(sec) = (((void*)(sec)) + sizeof(struct section));
		y++;
		(*ycount)++;
	}
}

void handle_32(char * ptr)
{
	int ncmds;
	struct load_command *lc;
	struct symtab_command *sym;
	int i;
	int ycount;

	t_line			*line;
	ncmds  = ((struct mach_header *)ptr)->ncmds;
	lc = (void *)ptr + sizeof(struct mach_header);
	i = 0;
	ycount = 1;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			line = get_line_32(sym->nsyms, sym->symoff, sym->stroff, ptr);
			tri_pourri_lol(&line);
			print_line(line);
			exit(0);
		}
		else if (lc->cmd == LC_SEGMENT)
			handle_32_segment(lc, &ycount);
		lc = (void*) lc + lc ->cmdsize;
	}
}


void nm(char *ptr)
{
	unsigned int magic_number;
	struct fat_arch		*arch;
	uint32_t	i;
	char *cpy;

	ft_bzero(&command, sizeof(command));
	magic_number = *(int*) ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_number == MH_MAGIC)
		handle_32(ptr);
	else if (magic_number == FAT_CIGAM)
	{
		i = 0;
		while (i < ft_nxswaplong(((struct fat_header*)ptr)->nfat_arch))
		{
			arch = (struct fat_arch*)(ptr + (sizeof(struct fat_header))) + i++;
			if (ft_nxswaplong(arch->cputype) == CPU_TYPE_X86_64)
			{
				cpy = ft_memdup(ptr + ft_nxswaplong(arch->offset), ft_nxswaplong(arch->size));
				handle_64(cpy);
				free(cpy);
			}
		}
	}
}

int main(int ac, char **av)
{
	int		fd;
	char	*ptr;
	struct stat	buf;

	if (ac > 1)
	{
		if ((fd = open(av[1], O_RDONLY)) < 0)
			exit(0);
	}
	else
	{
		if ((fd = open("a.out", O_RDONLY)) < 0)
			exit(0);
	}
	if (fstat(fd, &buf) < 0)
		exit(0);
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		exit(0);
	antitroll(ptr, buf.st_size);
	nm(ptr);
	exit(0);
}
