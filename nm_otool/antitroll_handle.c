/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antitroll_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 04:14:56 by mprevot           #+#    #+#             */
/*   Updated: 2018/12/15 04:15:12 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "antitroll.h"

void		handle_64_trololo_segment(
	void *ptr, off_t size, void *lc, int *ycount)
{
	struct section_64		*sec;
	uint32_t				y;

	ifexit((size < lc - ptr + (off_t)sizeof(struct segment_command_64)), 48);
	sec = (lc + sizeof(struct segment_command_64));
	y = 0;
	while (y < ((struct segment_command_64 *)(lc))->nsects)
	{
		ifexit((size < (((void*)sec) - ptr) + (off_t)sizeof(*sec)), 48);
		(sec) = (((void*)(sec)) + sizeof(struct section_64));
		y++;
		(*ycount)++;
	}
}

void		handle_64_trololo(char *ptr, off_t size)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	uint32_t				i;
	int						ycount;

	i = 0;
	ycount = 1;
	ifexit((size < (off_t)sizeof(*header) + (off_t)sizeof(*lc)), 46);
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*header);
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			ifexit((size < (((void*)lc)
				- ((void*)ptr)) + (off_t)sizeof(*lc)), 47);
			get_line_trololo((struct symtab_command *)lc, ptr, size);
			return ;
		}
		else if (lc->cmd == LC_SEGMENT_64)
			handle_64_trololo_segment(ptr, size, lc, &ycount);
		ifexit((size < (((void*)lc) - ((void*)ptr)) + lc->cmdsize), 45);
		lc = (void*)lc + lc->cmdsize;
	}
}

void		handle_32_trololo_segment(
	void *ptr, off_t size, void *lc, int *ycount)
{
	struct section			*sec;
	uint32_t				y;

	ifexit((size < lc - ptr + (off_t)sizeof(struct segment_command)), 48);
	sec = (lc + sizeof(struct segment_command));
	y = 0;
	while (y < ((struct segment_command *)(lc))->nsects)
	{
		ifexit((size < (((void*)sec) - ptr) + (off_t)sizeof(*sec)), 48);
		(sec) = (((void*)(sec)) + sizeof(struct section));
		y++;
		(*ycount)++;
	}
}

void		handle_32_trololo(char *ptr, off_t size)
{
	struct mach_header		*header;
	struct load_command		*lc;
	uint32_t				i;
	int						ycount;

	i = 0;
	ycount = 1;
	ifexit((size < (off_t)sizeof(struct mach_header)
		+ (off_t)sizeof(struct load_command)), 46);
	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(*header);
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			ifexit((size < (((void*)lc) - ((void*)ptr))
				+ (off_t)sizeof(struct load_command)), 47);
			get_line_trololo_32((struct symtab_command *)lc, ptr, size);
			return ;
		}
		else if (lc->cmd == LC_SEGMENT)
			handle_32_trololo_segment(ptr, size, lc, &ycount);
		ifexit((size < (((void*)lc) - ((void*)ptr)) + lc->cmdsize), 45);
		lc = (void*)lc + lc->cmdsize;
	}
}

void		handle_fat_trololo(char *ptr, off_t size)
{
	uint32_t				i;
	char					*cpy;
	struct fat_header		*fat;
	struct fat_arch			*arch;

	fat = (struct fat_header*)ptr;
	i = 0;
	ifexit((size < (off_t)sizeof(struct fat_header)
		+ (off_t)sizeof(struct fat_arch) * nsl(fat->nfat_arch)), 43);
	while (i < nsl(fat->nfat_arch))
	{
		arch = (struct fat_arch*)(ptr + (sizeof(struct fat_header))) + i;
		if (nsl(arch->cputype) == CPU_TYPE_X86_64)
		{
			ifexit((size < nsl(arch->offset) + nsl(arch->size)), 44);
			cpy = ft_memdup(ptr + nsl(arch->offset), nsl(arch->size));
			handle_64_trololo(cpy, nsl(arch->size));
			free(cpy);
		}
		i++;
	}
}
