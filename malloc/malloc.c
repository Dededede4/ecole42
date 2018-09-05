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



/////

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

static void	ft_putnbr_fd_hexa(size_t n, int fd)
{
	if (n >= 16)
	{
		ft_putnbr_fd_hexa(n / 16, fd);
		ft_putnbr_fd_hexa(n % 16, fd);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd(n + '0', fd);
		else
			ft_putchar_fd((n - 10) + 'A', fd);
	}
}


void	ft_putstr(char const *s)
{
	while (*s)
		ft_putchar_fd(*(s++), 1);
}

/////


static t_list *find_item_list(void *addr, t_list **page_container)
{
	t_list    *current;

	current = *page_container;
	while(current)
	{
	    if (current->data == addr)
	    {
            return current;
        }
        current = current->next;
    }
	return (NULL);
}

static t_list *find_item(void *addr)
{
	t_list *r;

	if ((r = find_item_list(addr, &g_container.tiny)))
		return (r);
	if ((r = find_item_list(addr, &g_container.small)))
		return (r);
	if ((r = find_item_list(addr, &g_container.large)))
		return (r);
    return (NULL);
}



void display_pages(){
	return ;
	t_list *current;
	size_t poid;

	ft_putstr("====== DÉBUT ======\n");
	current = g_container.tiny;
	poid = 0;
	while(current)
	{
		if (current->is_new_page)
		{
			if(poid != 0)
			{
				ft_putstr("Total : ");
				ft_putnbr_fd(poid, 1);
				ft_putstr(" octets\n");
				poid = 0;
			}
			ft_putstr("\n\nNouvelle page :\n");
		}
		
		
		ft_putnbr_fd_hexa((size_t)current, 1);
		ft_putstr(" Bloc de ");
		ft_putnbr_fd(current->data_size, 1);
		ft_putstr(" octets\n");
		poid += current->data_size + sizeof(t_list);
		current = current->next;
	}
	ft_putstr("Poid restant : ");
	ft_putnbr_fd(poid, 1);
	ft_putstr(" octets\n");
}





static t_list	*malloc_direct(size_t size)
{
	size_t	size_alloc;
	t_list	*l;

	size_alloc = size + sizeof(t_list);
	size_alloc = ((size_alloc / getpagesize()) + 1) * getpagesize();
	l = mmap(NULL, size_alloc, PROT_READ | PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	l->data_size = size;
	l->data = l + 1;
	l->is_busy = 9;
	l->is_new_page = 1;
	l->next = NULL;
	return (l);
}

// Entre 1 et (1024 - taille de la structure)
static t_list	*malloc_page_list(size_t size, t_list **page_container)
{
	t_list *current;

	if (*page_container)
	{
		current = *page_container;
		while (current->next)
		{
			current = current->next;
		}
		current->next = malloc_direct(size);
		return (current->next);
	}
	else
	{
		*page_container = malloc_direct(size);
		return (*page_container);
	}
}



static t_list	*malloc_page_large(size_t size)
{
	t_list *current;
	static char first = 0;
	if (!first)
	{
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
		return (g_container.large);
	}
}

static t_list *malloc_nopage_list(size_t size, t_list **container)
{
	t_list *current;

	current = *container;
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

static void *	malloc_list(size_t size, t_list **page_container)
{
	size_t page_used_size;
	t_list	*last;
	t_list *l;
	t_list *page;

	page = *page_container;
	if (NULL == *page_container)
	{
		l = malloc_page_list(size, page_container);
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
	if ((getpagesize() - (page_used_size + sizeof(t_list))) > (sizeof(t_list) + size))
	{
		l = malloc_nopage_list(size, page_container);
		return (l->data);
	}
	l = malloc_page_list(size, page_container);
	return (l->data);
}


static void *malloc_large(size_t size)
{
	t_list *pouet = malloc_page_large(size);
	return (pouet->data);
}

void	*ft_malloc(size_t size)
{
	void *ret;
	if (size == 0)
		return (NULL);
	if ((size * 4) <= getpagesize() - sizeof(t_list))
		ret = malloc_list(size, &g_container.tiny);
	else if (size <= getpagesize() - sizeof(t_list))
		ret = malloc_list(size, &g_container.small);
	else
		ret = malloc_large(size);
	return (ret);
}

#include <time.h>
#include <stdlib.h>

static size_t show_alloc_mem_list(char *name, t_list **container)
{
	t_list *current;
	size_t	total;

	total = 0;
	current = *container;
	ft_putstr(name);
	ft_putstr(" : 0x");
	ft_putnbr_fd_hexa((size_t)*container, 1);
	ft_putstr("\n");
	while (current)
	{
		ft_putstr("0x");
		ft_putnbr_fd_hexa((size_t)current->data, 1);
		ft_putstr(" - 0x");
		ft_putnbr_fd_hexa((size_t)(current->data + current->data_size), 1);
		ft_putstr(" : ");
		ft_putnbr_fd((size_t)(current->data_size), 1);
		ft_putstr("\n");
		total += current->data_size;
		current = current->next;
	}
	return total;
}

void show_alloc_mem()
{
	size_t total;

	total = show_alloc_mem_list("TINY", &g_container.tiny);
	total += show_alloc_mem_list("SMALL", &g_container.small);
	total += show_alloc_mem_list("LARGE", &g_container.large);
	ft_putstr("Total : ");
	ft_putnbr_fd(total, 1);
	ft_putstr(" octets\n");
}

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

static void ft_free_container(void *addr, t_list **page_container)
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
	page_start = *page_container;
	before_page_start = NULL;
	current = page_start->next;
	busy_find = false;
	while(current)
	{
		if (current->is_new_page || current->next == NULL)
		{
			if (!busy_find)
			{
				
				if (before_page_start == NULL)
				{
					if (current->next == NULL)
					{
						*page_container = NULL;
					}
					else
					{
						*page_container = current;
					}
				}
				else
				{
					before_page_start->next = current;
					before_page_start = old_current;
				}
				munmap(page_start, getpagesize());
				return;
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
 	ft_free_large(addr);
 	ft_free_container(addr, &g_container.tiny);
 	ft_free_container(addr, &g_container.small);
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

	if(ptr == NULL)
		return malloc(size);
	if(size == 0)
	{
		free(ptr);
		return (NULL);
	}
	
	
	
	new = ft_malloc(size);
	item = find_item(ptr);
	//write(1, "\x1B[31mft_realloc(", 16);
	if (item)
	{
		//ft_putnbr_fd(item->data_size - size, 1);
		//ft_putnbr_fd(item->data_size, 1);
		//ft_putstr(" ");
		//ft_putnbr_fd(size, 1);
		ft_memcpy(new, ptr, item->data_size < size ? item->data_size : size);
	}
	else
	{
		//ft_putnbr_fd(size, 1);
		return (NULL);
	}
	//write(1, ");\x1B[0m\n", 7);
	ft_free(ptr);
	return (new);
}

void free(void *ptr)
{
	return (ft_free(ptr));
}

void *malloc(size_t size)
{
	return ft_malloc(size);
}

void *realloc(void *ptr, size_t size)
{
	return (ft_realloc(ptr, size));
}

static void main_test_0()
{
	(void)malloc(42);
	(void)malloc(84);
	(void)malloc(3725);
	(void)malloc(48847);
	show_alloc_mem();
}

static void main_test_1()
{
	show_alloc_mem();
	void *a = malloc(42);
	void *b = malloc(84);
	(void)malloc(3725);
	(void)malloc(48847);
	free(a);
	free(b);
	show_alloc_mem();
}

int main()
{
	main_test_1();
	return (0);
}
/*
int main(void)
{
	printf("%p\n", ft_malloc(32));
	printf("%p\n", ft_malloc(32));
	printf("%p\n", ft_malloc(32));
	printf("%p\n", ft_malloc(15));
	printf("%p\n", ft_malloc(45));
	printf("%p\n", ft_malloc(205));
	printf("%p\n", ft_malloc(45));
	printf("%p\n", ft_malloc(50));
	printf("%p\n", ft_malloc(47));
	printf("%p\n", ft_malloc(11));
	printf("%p\n", ft_malloc(64));
	printf("%p\n", ft_malloc(49));
	printf("%p\n", ft_malloc(67));
	printf("%p\n", ft_malloc(52));
	printf("%p\n", ft_malloc(54));
	printf("%p\n", ft_malloc(12));
	printf("%p\n", ft_malloc(45));
	printf("%p\n", ft_malloc(80));
	printf("%p\n", ft_malloc(16));
	printf("%p\n", ft_malloc(64));
	printf("%p\n", ft_malloc(14));
	printf("%p\n", ft_malloc(256));
	printf("%p\n", ft_malloc(4096));
	printf("%p\n", ft_malloc(2160));
	char *a = ft_malloc(3312);
	a[3311] = 5;
	printf("%p\n", ft_malloc(4096));
	char *bb = ft_realloc(a, 91556);
	ft_putnbr_fd((size_t)bb[3311], 1);
	printf("%p\n", ft_malloc(192));
	printf("%p\n", ft_malloc(46));
	printf("%p\n", ft_malloc(48));
	printf("%p\n", ft_malloc(20));
	printf("%p\n", ft_malloc(488));
	char *b = ft_malloc(389);
	b[388] = 'a';
}*/
