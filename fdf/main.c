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

int	on_key_press(int keycode, void *param)
{
	(void)(param);
	if (keycode == 53)
		exit (0);
	return 1;
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
		if ((i + 1) % width != 0)
			ft_mlx_3draw(mlx, win, *(positions[i]), *(positions[i + 1]));
		if (i + width < len)
			ft_mlx_3draw(mlx, win, *(positions[i]), *(positions[i + width]));
		i++;
	}

	mlx_key_hook(win, on_key_press, NULL);

	mlx_loop(mlx);	
}
