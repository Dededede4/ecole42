/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:11:29 by mprevot           #+#    #+#             */
/*   Updated: 2018/11/25 17:12:19 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

typedef struct					s_command
{
	char						*path;
	int							fd;
	char						*ptr;
	struct stat					buf;
	int							magic_number;
	int							ncmds;
	struct load_command			*lc;
	struct symtab_command		*sym;

	struct mach_header_64		*header_64;
	struct segment_command_64	*seg_64;
	struct section_64			*sec_64;
	//struct nlist_64				*el_64;

	struct mach_header		*header_32;
	struct segment_command	*seg_32;
	struct section			*sec_32;
	//struct nlist				*el_32;	
}								t_command;

#endif
