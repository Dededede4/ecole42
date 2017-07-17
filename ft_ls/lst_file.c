/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstFile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <mprevot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 18:17:52 by mprevot           #+#    #+#             */
/*   Updated: 2014/12/05 11:20:02 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	lst_file_add_end(t_file *file, t_file *new_file)
{
	while (file->next)
		file = file->next;
	file->next = new_file;
}

void	lst_path_add_end(t_path *file, t_path *new_file)
{
	while (file->next)
		file = file->next;
	file->next = new_file;
}

size_t	lst_len(t_file *file)
{
	size_t i;

	i = 0;
	while (file && ++i)
		file = file->next;
	return (i);
}

size_t	lst_len_path(t_path *file)
{
	size_t i;

	i = 0;
	while (file && ++i)
		file = file->next;
	return (i);
}
