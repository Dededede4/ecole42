#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

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

t_all g_container;

void	init_container()
{
	g_container.large = NULL;
	g_container.small = NULL;
	g_container.tiny = NULL;
	g_container.nbr_large = 0;
	g_container.nbr_small = 0;
	g_container.nbr_tiny = 0;
}

t_list	*malloc_direct(size_t size)
{
	size_t	size_alloc;
	t_list	*l;

	size_alloc = size + sizeof(t_list);
	size_alloc = ((size_alloc / getpagesize()) + 1) * getpagesize();
	l = mmap(NULL, size_alloc, PROT_READ | PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);
	l->data_size = size;
	l->data = l + 1;
	l->is_busy = 9;
	l->is_new_page = 1;
	l->next = NULL;
	return (l);
}

// Entre 1 et (1024 - taille de la structure)
t_list	*malloc_page_tiny(size_t size)
{
	t_list *current;
	g_container.nbr_tiny++;
	if (g_container.tiny)
	{
		current = g_container.tiny;
		while (current->next)
		{
			current = current->next;
		}
		current->next = malloc_direct(size);
		return (current->next);
	}
	else
	{
		g_container.tiny = malloc_direct(size);
		return (g_container.tiny);
	}
}

t_list	*malloc_page_small(size_t size)
{
	t_list *current;
	g_container.nbr_small++;
	if (g_container.small)
	{
		current = g_container.small;
		while (current->next)
		{
			current = current->next;
		}
		current->next = malloc_direct(size);
		return (current->next);
	}
	else
	{
		g_container.small = malloc_direct(size);
		return (g_container.small);
	}
}

t_list	*malloc_page_large(size_t size)
{
	t_list *current;
	g_container.nbr_large++;
	if (g_container.large)
	{
		current = g_container.large;
		while (current->next)
		{
			current = current->next;
		}
		current->next = malloc_direct(size);
		return (current->next);
	}
	else
	{
		g_container.large = malloc_direct(size);
		return (g_container.large);
	}
}

t_list *malloc_nopage_tiny(size_t size)
{
	t_list *current;

	current = g_container.tiny;
	while (current->next)
	{
		current = current->next;
	}
	current->next = current->data + current->data_size;
	current->next->next = NULL;
	current->next->data = current->next + 1;
	current->next->is_busy = 1;
	current->next->data_size = size;
	current->next->is_new_page = 0;
	return (current->next);
}

t_list *malloc_nopage_small(size_t size)
{
	t_list *current;

	current = g_container.small;
	while (current->next)
	{
		current = current->next;
	}
	current->next = current->data + current->data_size;
	current->next->next = NULL;
	current->next->data = current->next + 1;
	current->next->is_busy = 1;
	current->next->data_size = size;
	current->next->is_new_page = 0;
	return (current->next);
}

size_t	list_size(t_list *page)
{
	size_t size;

	size = 0;
	while(page)
	{
		size += page->data_size + sizeof(t_list);
		page = page->next;
	}
	return (size);
}


void *	malloc_tiny(size_t size)
{
	size_t page_used_size;
	t_list	*last;
	t_list *l;
	t_list *page;

	page = g_container.tiny;
	if (NULL == g_container.tiny)
	{
		l = malloc_page_tiny(size);
		return (l->data);
	}
	page_used_size = 0;
	while(page)
	{
		page_used_size += page->data_size + sizeof(t_list);
		if (page->next && page->next->is_new_page)
		{

			if ((getpagesize() - page_used_size) > (sizeof(t_list) + size))
			{
				l = page->next;
				page->next = page->data + page->data_size;
				page->next->next = l;
				page->next->data = page->next + 1;
				page->next->is_busy = 1;
				page->next->data_size = size;
				page->next->is_new_page = 0;
				return (page->data);
			}
			page_used_size = 0;
		}
		last = page;
		page = page->next;
	}
	if ((getpagesize() - page_used_size) > (sizeof(t_list) + size))
	{
		l = malloc_nopage_tiny(size);
		return (l->data);
	}
	l = malloc_page_tiny(size);
	return (l->data);
}

void *	malloc_small(size_t size)
{
	size_t page_used_size;
	t_list	*last;
	t_list *l;
	t_list *page;

	page = g_container.small;
	if (NULL == g_container.small)
	{
		l = malloc_page_small(size);
		return (l->data);
	}
	page_used_size = 0;
	while(page)
	{
		page_used_size += page->data_size + sizeof(t_list);
		if (page->next && page->next->is_new_page)
		{

			if ((getpagesize() - page_used_size) > (sizeof(t_list) + size))
			{
				l = page->next;
				page->next = page->data + page->data_size;
				page->next->next = l;
				page->next->data = page->next + 1;
				page->next->is_busy = 1;
				page->next->data_size = size;
				page->next->is_new_page = 0;
				return (page->data);
			}
			page_used_size = 0;
		}
		last = page;
		page = page->next;
	}
	if ((getpagesize() - page_used_size) > (sizeof(t_list) + size))
	{
		l = malloc_nopage_small(size);
		return (l->data);
	}
	l = malloc_page_small(size);
	return (l->data);
}

void *malloc_large(size_t size)
{
	return malloc_page_large(size);
}

void	*ft_malloc(size_t size)
{
	if ((size * 4) <= getpagesize() - sizeof(t_list))
		return malloc_tiny(size);
	if (size <= getpagesize() - sizeof(t_list))
		return malloc_small(size);
	return malloc_large(size);
}

void	memdump(void *data)
{
	size_t i;

	i = 0;
	printf("\n===========\n");
	while(i < 4096)
	{
		printf("%02hhX ", (unsigned char)(*(char*)(data + i)));
		if ((i + 1)  % sizeof(t_list) == 0)
			printf("\n");
		i++;
	}
	printf("\n===========\n");
}

#include <time.h>
#include <stdlib.h>

void show_alloc_mem()
{
	t_list *current;
	size_t	total;

	total = 0;
	current = g_container.tiny;
	printf("TINY : %p\n", current);
	while (current)
	{
		printf("%p - %p : %zu octets\n", current->data, current->data + current->data_size, current->data_size );
		total += current->data_size;
		current = current->next;
	}
	current = g_container.small;
	printf("SMALL : %p\n", current);
	while (current)
	{
		printf("%p - %p : %zu octets\n", current->data, current->data + current->data_size, current->data_size );
		total += current->data_size;
		current = current->next;
	}
	current = g_container.large;
	printf("LARGE : %p\n", current);
	while (current)
	{
		printf("%p - %p : %zu octets\n", current->data, current->data + current->data_size, current->data_size );
		total += current->data_size;
		current = current->next;
	}
	printf("TOTAL : %zu octets\n", total);
//	Total : 52698 octets
}

int 	main()
{
	init_container();
	printf("coucou bg 42");
	/*char *str;
	int i = 0;
	srand(time(NULL));
	while (i < 10) {
		str = ft_malloc(rand() % 10000);
		strcpy(str, "abcd");
		printf("%s %d %d %d\n", str, i, (int)g_container.nbr_tiny, (int)((getpagesize() * g_container.nbr_tiny) - list_size(g_container.tiny)));
		//memdump(g_container.tiny);
		i++;
	}*/
	ft_malloc(42);
	ft_malloc(84);
	ft_malloc(3725);
	ft_malloc(48847);
	show_alloc_mem();

	return (0);	
}

