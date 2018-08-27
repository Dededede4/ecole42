#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
//static void show_alloc_mem();

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

t_all g_container = {NULL, NULL, NULL, 0, 0, 0};

static t_list *find_item(void *addr)
{
	t_list    *current;

	current = g_container.tiny;
	while(current)
	{
	    if (current == addr)
	    {
            return current;
        }
        current = current->next;
    }

    current = g_container.small;
	while(current)
	{
	    if (current == addr)
	    {
            return current;
        }
        current = current->next;
    }

    current = g_container.large;
	while(current)
	{
	    if (current == addr)
	    {
            return current;
        }
        current = current->next;
    }

    return (NULL);
}

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putnbr_fd(size_t n, int fd)
{
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		ft_putchar_fd(n + '0', fd);
	}
}

void	ft_putstr(char const *s)
{
	while (*s)
		ft_putchar_fd(*(s++), 1);
}





	// g_container.large = NULL;
	// g_container.small = NULL;
	// g_container.tiny = NULL;
	// g_container.nbr_large = 0;
	// g_container.nbr_small = 0;
	// g_container.nbr_tiny = 0;


static t_list	*malloc_direct(size_t size)
{
	size_t	size_alloc;
	t_list	*l;

	size_alloc = size + sizeof(t_list);
	size_alloc = ((size_alloc / getpagesize()) + 1) * getpagesize();
	ft_putnbr_fd(size_alloc, 1);
	ft_putstr("<-malloc direct\n");
	l = mmap(NULL, size_alloc, PROT_READ | PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	l->data_size = size;
	l->data = l + 1;
	l->is_busy = 9;
	l->is_new_page = 1;
	l->next = NULL;
	return (l);
}

// Entre 1 et (1024 - taille de la structure)
static t_list	*malloc_page_tiny(size_t size)
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

static t_list	*malloc_page_small(size_t size)
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

static t_list	*malloc_page_large(size_t size)
{
	t_list *current;
	static char first = 0;
	if (!first)
	{
		ft_putnbr_fd(size, 1);
		ft_putstr("<-first\n");
		g_container.large = NULL;
		g_container.nbr_large = 0;
		first = 1;
	}

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
		ft_putnbr_fd(g_container.large->data_size, 1);
		ft_putstr("<-last\n");
		return (g_container.large);
	}
}

static t_list *malloc_nopage_tiny(size_t size)
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

static t_list *malloc_nopage_small(size_t size)
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

/*static size_t	list_size(t_list *page)
{
	size_t size;

	size = 0;
	while(page)
	{
		size += page->data_size + sizeof(t_list);
		page = page->next;
	}
	return (size);
}*/


static void *	malloc_tiny(size_t size)
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

			if ((getpagesize() - page_used_size) > (sizeof(t_list) + size)) // On segfault sur ls ! o_O
			{
				l = page->next;
				page->next = page->data + page->data_size +1;
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
		ft_putstr("b\n");
		return (l->data);
	}
	l = malloc_page_tiny(size);
	ft_putstr("c\n");
	return (l->data);
}

static void *	malloc_small(size_t size)
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

static void *malloc_large(size_t size)
{
	t_list *pouet = malloc_page_large(size);
	return (pouet->data);
}

void	*ft_malloc(size_t size)
{
	if (size == 0)
		return (NULL);
	write(1, "\x1B[31mmalloc(", 12);
	ft_putnbr_fd(size, 1);
	write(1, ");\x1B[0m\n", 7);
	//printf("\nmalloc(%zu);\n", size);
	if ((size * 4) <= getpagesize() - sizeof(t_list))
		return malloc_tiny(size);
	if (size <= getpagesize() - sizeof(t_list))
		return malloc_small(size);
	return malloc_large(size);
}

/*static void	memdump(void *data)
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
*/
#include <time.h>
#include <stdlib.h>

/*static void show_alloc_mem()
{
	t_list *current;
	size_t	total;

	total = 0;
	current = g_container.tiny;
	//printf("TINY : %p\n", current);
	ft_putstr("TINY :\n");
	while (current)
	{
		ft_putstr("%p - %p : ");
		ft_putnbr_fd(current->data_size, 1);
		ft_putstr("\n");
		//printf("%p - %p : %zu octets\n", current->data, current->data + current->data_size, current->data_size );
		total += current->data_size;
		current = current->next;
	}
	ft_putstr("SMALL :\n");
	current = g_container.small;
	//printf("SMALL : %p\n", current);
	while (current)
	{
		ft_putstr("%p - %p : ");
		ft_putnbr_fd(current->data_size, 1);
		ft_putstr("\n");
		//printf("%p - %p : %zu octets\n", current->data, current->data + current->data_size, current->data_size );
		total += current->data_size;
		current = current->next;
	}
	ft_putstr("LARGE :\n");
	current = g_container.large;
	//printf("LARGE : %p\n", current);
	while (current)
	{
		ft_putstr("%p - %p : ");
		ft_putnbr_fd(current->data_size, 1);
		ft_putstr("\n");
		//printf("%p - %p : %zu octets\n", current->data, current->data + current->data_size, current->data_size );
		total += current->data_size;
		current = current->next;
	}
	//printf("TOTAL : %zu octets\n", total);
//	Total : 52698 octets
}*/

static void ft_free_large(void *addr)
{
    t_list    *current;
    t_list    *before;
    size_t	size_alloc;

	

	current = g_container.large;
	before = NULL;
	while(current)
	{
	    if (current == addr)
	    {
			size_alloc = current->data_size + sizeof(t_list);
			size_alloc = ((size_alloc / getpagesize()) + 1) * getpagesize();
	        if(NULL == before)
	        {
				g_container.large = current->next;
				munmap(current, size_alloc);
				return ;
            }
            before->next = current->next;
            munmap(current, size_alloc);
            return ;
        }
        before = current;
        current = current->next;
    }
}

static void ft_free_tiny(void *addr)
{
    t_list    *current;
    t_list	  *page_start;
    t_list	  *before_page_start;
    t_list	  *old_current;
    bool	  busy_find;

	if(!(current = find_item(addr)))
		return ;
	current->is_busy = 0;

	// petit algo pour parcourir les élèments de la liste, si entre deux pages tout est vide, on peut le free pour de vrai.
	page_start = g_container.tiny;
	before_page_start = NULL;
	current = page_start->next;
	busy_find = false;
	while(current)
	{
		if (current->is_new_page || current->next == NULL)
		{
			if (!busy_find)
			{
				ft_putstr("bite\n");
				munmap(page_start, getpagesize());
				if (before_page_start == NULL)
				{
					g_container.tiny = current;
				}
				else
				{
					before_page_start->next = current;
					before_page_start = old_current;
				}
			}
			busy_find = false;
			page_start = current;
		}
		if (current->is_busy)
		{
			busy_find = true;
		}
		old_current = current;
		current = current->next;
	}
}

void ft_free(void *addr)
{
	(void)addr;
	write(1, "\x1B[31mfree();\n", 14);
	//show_alloc_mem();
 	ft_free_large(addr);
 	ft_free_tiny(addr);
}

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
	return (dest);
}

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*b2;

	i = 0;
	b2 = b;
	while (i < len)
	{
		b2[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void *ft_realloc(void *ptr, size_t size)
{
	void *new;
	t_list *item;

	write(1, "\x1B[31mft_realloc(", 13);
	ft_putnbr_fd(size, 1);
	write(1, ");\x1B[0m\n", 7);
	new = ft_malloc(size);
	ft_memset(new, 0, size);
	item = find_item(ptr);
	if (item)
	{
		ft_memcpy(new, ptr, item->data_size < size ? item->data_size : size);
	}
	ft_free(ptr);
	return (new);
}

void free(void *ptr)
{
	return (ft_free(ptr));
}

void *malloc(size_t size)
{
	return (ft_malloc(size));
}

void *realloc(void *ptr, size_t size)
{
	return (ft_realloc(ptr, size));
}

int main(void)
{

	void *lol = ft_malloc(10);
	void *lol2 = ft_malloc(10);
	void *lol3 = ft_malloc(10);
	ft_free(lol);
	ft_free(lol2);
	ft_free(lol3);
	return (0);
}
