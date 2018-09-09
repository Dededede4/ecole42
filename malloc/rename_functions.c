/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 20:05:01 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 20:05:04 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free(void *ptr)
{
	return (ft_free(ptr));
}

void	*malloc(size_t size)
{
	return (ft_malloc(size));
}

void	*realloc(void *ptr, size_t size)
{
	return (ft_realloc(ptr, size));
}
