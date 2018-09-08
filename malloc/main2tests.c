
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

static void main_test_2()
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
	char *bb = ft_realloc(a, 91556);
	ft_putnbr_fd((size_t)bb[3311], 1);
	printf("%p\n", ft_malloc(192));
	printf("%p\n", ft_malloc(46));
	printf("%p\n", ft_malloc(48));
	printf("%p\n", ft_malloc(20));
	printf("%p\n", ft_malloc(488));
	char *b = ft_malloc(389);
	b[388] = 'a';
}

int main()
{
	main_test_2();
	return (0);
}
