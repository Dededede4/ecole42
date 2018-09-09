/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 22:27:57 by mprevot           #+#    #+#             */
/*   Updated: 2018/09/08 22:28:14 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct		s_list
{
	void 			*data;
	char			is_busy;
	char			is_new_page;
	size_t			data_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_all
{
	t_list		*large;
	t_list		*small;
	t_list		*tiny;
	size_t		nbr_large;
	size_t		nbr_small;
	size_t		nbr_tiny;
}			t_all;

extern t_all g_container;
//t_all g_container = {NULL, NULL, NULL, 0, 0, 0};

# define DEBUG_MALLOC 1

t_list	*find_item_list(void *addr, t_list **page_container); 

t_list	*find_item(void *addr);

void	ft_free_large(void *addr);
void	ft_free_container_checkmunmap_nobusyfind(
	t_list **page_container, t_list *before_page_start,
	t_list *current, t_list *page_start);
void	ft_free_container_checkmunmap(t_list **page_container);
void	ft_free_container(void *addr, t_list **page_container);
void	ft_free(void *addr);

void	*ft_malloc(size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);

void	ft_putnbr_fd(size_t n, int fd);
void	ft_putnbr_fd_hexa(size_t n, int fd);
int	ft_putnbr_fd_debug(size_t n, int fd);

void		ft_putchar_fd(char c, int fd);
void			ft_putstr(char const *s);
int		ft_putstr_debug(char const *s);
int		pd(char const *s);

void		*ft_realloc_afterchecks(void *ptr, size_t size);
void		*ft_realloc(void *ptr, size_t size);

t_list	*malloc_direct(size_t size);

void		*malloc_large(size_t size);

void		*create_zone_from_mem(t_list *page, size_t size);
void		*malloc_list_after(size_t size, t_list **page_container,
	size_t page_used_size);
void		*malloc_list(size_t size, t_list **page_container);


t_list	*malloc_nopage_list(size_t size, t_list **container);

t_list	*malloc_page_large(size_t size);

t_list	*malloc_page_list(size_t size, t_list **page_container);

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

size_t	show_alloc_mem_list(char *name, t_list **container);
void			show_alloc_mem(void);

t_all	get_container(void);

#endif