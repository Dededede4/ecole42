#include "fdf.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit(0);
}

void ft_strsplit_del(char ***str)
{
	int i;
	char *line;

	i = 0;
	while ((*str)[i])
	{
		line = (*str)[i];
		ft_strdel(&line);
		i++;
	}
	line = (*str)[i];
	ft_strdel(&line);
	free(*str);
	*str = NULL;
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
					ft_error("Error (no an digit)\n");
				i++;
			}
			if (nbr == -1)
				nbr = i;
			else if (nbr != i)
				ft_error("Error (no an rectangle)\n");
			i++;
			total += nbr;
			ft_memdel((void**)&line);
			ft_strsplit_del(&splited);
		}
	}
	else
		ft_error("Error (bad file)\n");
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
				positions[i] = ft_mlx_mallocposition(x * 10, y * 10 + 200, 200 - (ft_atoi(splited[x])) * 1);
				x++;
				i++;
			}
			ft_memdel((void**)&line);
			ft_strsplit_del(&splited);
			y++;
		}
		close(fd);
		return (positions);
	}
	close(fd);
	ft_error("Error (bad file)\n");
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
		ft_error("Usage : ./fdf file.fdf\n");
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
	exit(0);
	return (0);
}
