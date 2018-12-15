/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 02:46:14 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/15 02:46:16 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	handle_64_segment(void *lc, int *ycount)
{
	struct section_64		*sec_64;
	uint32_t				y;

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

void	handle_64(char *ptr)
{
	int						ncmds;
	struct load_command		*lc;
	int						i;
	int						ycount;
	t_line					*line;

	ncmds = ((struct mach_header_64*)ptr)->ncmds;
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
		lc = (void*)lc + lc->cmdsize;
	}
}

void	handle_32_segment(void *lc, int *ycount)
{
	struct section			*sec;
	uint32_t				y;

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

void	handle_32(char *ptr)
{
	struct load_command		*lc;
	struct symtab_command	*sym;
	unsigned int			i;
	int						ycount;
	t_line					*line;

	lc = (void *)ptr + sizeof(struct mach_header);
	i = 0;
	ycount = 1;
	while (i++ < ((struct mach_header *)ptr)->ncmds)
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
		lc = (void*)lc + lc->cmdsize;
	}
}
