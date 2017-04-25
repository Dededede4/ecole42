#include "fdf.h"

int 	count(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int 	check_validity(char *path, int *width){
	int fd;
	int nbr;
	char *line;
	char **splited;
	int i;
	int total;

	nbr = -1;
	line = NULL;
	i = 0;
	total = 0;
	fd = open(path, O_RDONLY);
	if (fd > -1)
	{
		while (ft_gnl(fd, &line))
		{
			i = 0;
			splited = ft_strsplit(line, ' ');
			while (splited[i])
			{
				if (!ft_isdigit_str(splited[i]))
				{
					// Error
				}
				i++;
			}
			if (nbr == -1)
				nbr = i;
			else if (nbr != i){
				// Error
			}
			i++;
			total += nbr;
			// free line
			// free strsplit
		}
	}
	else
	{
		// Error
	}
	close(fd);
	*width = nbr;
	return (total);
}


t_position 	**parsing(char *path, int width)
{
	char *line;
	char **splited;
	size_t x;
	size_t y;
	int i;
	t_position **positions;
	int fd;

	positions = ft_memalloc((width + 1 )* sizeof(NULL));
	y = 0;
	line = NULL;
	fd = open(path, O_RDONLY);
	i = 0;
	if (fd > -1)
	{
		while(ft_gnl(fd, &line))
		{
			x = 0;
			splited = ft_strsplit(line, ' ');
			while(splited[x])
			{
				positions[i] = ft_mlx_mallocposition(x * 10, y * 10 + 200, 200 - (ft_atoi(splited[x])) *10);
				ft_printf("%s,", splited[x]);
				x++;
				i++;
			}
			ft_printf("\n");
			// free line
			// free splited
			y++;
		}
		close(fd);
		return (positions);
	}
	close(fd);
	// Error
	return (NULL);
}


int		main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	int 	width;
	int 	len;
	t_position **positions;
	int 	i;

	i = 0;
	if (argc != 2)
	{
		// Error ?
	}
	len = check_validity(argv[1], &width);
	positions = parsing(argv[1], len);

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 1000, "Coucou mon coco");
	while (positions[i + 1])
	{
		ft_printf("hey %i %% %i = %i\n", i + 1, width,  (i + 1) % width);
		if ((i + 1) % width != 0)
			ft_mlx_3draw(mlx, win, *(positions[i]), *(positions[i + 1]));
		if (i + width < len)
			ft_mlx_3draw(mlx, win, *(positions[i]), *(positions[i + width]));
		i++;
	}
	//ft_printf("--->%i\n", width);

	/*ft_mlx_3draw(mlx, win, ft_mlx_getposition(0, 0, 150), ft_mlx_getposition(0, 40, 150));
	ft_mlx_3draw(mlx, win, ft_mlx_getposition(0, 0, 150), ft_mlx_getposition(10, 0, 150));
	ft_mlx_3draw(mlx, win, ft_mlx_getposition(10, 0, 150), ft_mlx_getposition(10, 40, 150));
	ft_mlx_3draw(mlx, win, ft_mlx_getposition(0, 40, 150), ft_mlx_getposition(10, 40, 150));

	ft_mlx_3draw(mlx, win, ft_mlx_getposition(10, 0, 150), ft_mlx_getposition(10, 0, 200));
	ft_mlx_3draw(mlx, win, ft_mlx_getposition(0, 0, 150), ft_mlx_getposition(0, 0, 200));
	ft_mlx_3draw(mlx, win, ft_mlx_getposition(0, 40, 150), ft_mlx_getposition(0, 40, 200));
	ft_mlx_3draw(mlx, win, ft_mlx_getposition(10, 40, 150), ft_mlx_getposition(10, 40, 200));

	ft_mlx_3draw(mlx, win, ft_mlx_getposition(0, 0, 200), ft_mlx_getposition(0, 40, 200));
	ft_mlx_3draw(mlx, win, ft_mlx_getposition(0, 0, 200), ft_mlx_getposition(10, 0, 200));
	ft_mlx_3draw(mlx, win, ft_mlx_getposition(10, 0, 200), ft_mlx_getposition(10, 40, 200));
	ft_mlx_3draw(mlx, win, ft_mlx_getposition(0, 40, 200), ft_mlx_getposition(10, 40, 200));*/








	//ft_mlx_draw(mlx, win, ft_mlx_getpixel(10, 10), ft_mlx_getpixel(420, 420));
	/*
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(10, 10), ft_mlx_getpixel(12, 100));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(10, 10), ft_mlx_getpixel(25, 100));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(10, 10), ft_mlx_getpixel(100, 12));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(10, 10), ft_mlx_getpixel(100, 25));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(10, 10), ft_mlx_getpixel(100, 20));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(10, 10), ft_mlx_getpixel(100, 40));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(10, 10), ft_mlx_getpixel(100, 90));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(10, 10), ft_mlx_getpixel(500, 95));


	ft_mlx_draw(mlx, win, ft_mlx_getpixel(990-42, 990- 42), ft_mlx_getpixel(990, 990));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(990-12, 990-100), ft_mlx_getpixel(990, 990));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(990-25, 990-100), ft_mlx_getpixel(990, 990));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(900-100, 990- 12), ft_mlx_getpixel(990, 990));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(900-100, 990- 25), ft_mlx_getpixel(990, 990));

	ft_mlx_draw(mlx, win, ft_mlx_getpixel(990-42, 42), ft_mlx_getpixel(990, 10));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(990-12, 100), ft_mlx_getpixel(990, 10));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(990-25, 100), ft_mlx_getpixel(990, 10));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(900-100, 12), ft_mlx_getpixel(990, 10));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(900-100, 25), ft_mlx_getpixel(990, 10));

	ft_mlx_draw(mlx, win, ft_mlx_getpixel(42, 990- 42), ft_mlx_getpixel(10, 990));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(12, 990-100), ft_mlx_getpixel(10, 990));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(25, 990-100), ft_mlx_getpixel(10, 990));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(100, 990- 12), ft_mlx_getpixel(10, 990));
	ft_mlx_draw(mlx, win, ft_mlx_getpixel(100, 990- 25), ft_mlx_getpixel(10, 990));*/

	mlx_loop(mlx);	
}
