#include <stdlib.h>
#include <mlx.h>
#include <stdio.h>

typedef struct			s_pixel
{
	size_t				x;
	size_t				y;
	size_t				c;
}						t_pixel;


int 	ft_abs(int val)
{
	return ((val < 0) ? 0 - val : val);
}

t_pixel	new_pixel(size_t x, size_t y)
{
	t_pixel val;

	val.x = x;
	val.y = y;
	val.c = 0xfffff;
	return (val);
}

int	get_lenght_coef(t_pixel start, t_pixel stop, int *l, float *coef)
{
	int l1;
	int l2;
	float coef1;
	float coef2;

	l1 = ft_abs((int)(stop.x - start.x));
	l2 = ft_abs((int)(stop.y - start.y));
	*l = (l1 >= l2) ? l1 : l2;
	//*l = l1;
	coef1 = (float)l1 / l2;
	coef2 = (float)l2 / l1;
	//printf("l1 = %i, l2 = %i, r = %f\n", l1, l2, (int)l1 / l2);
	*coef = (coef1 <= coef2) ? coef1 : coef2;
	//*coef = coef2;
	//return (1);
	return (coef1 <= coef2) ? 0 : 1;
}

void	sort_pixels(t_pixel *start, t_pixel *stop)
{
	size_t x;
	size_t y;
	size_t c;

	if (start->x > stop->x)
	{
		printf("------>%i\n", (int)start->x);
		x = start->x;
		y = start->y;
		c = start->c;
		start->x = stop->x;
		start->y = stop->y;
		start->c = stop->c;
		stop->x = x;
		stop->y = y;
		stop->c = c;
	}
}

void	draw(void *mlx, void *win, t_pixel start, t_pixel stop)
{
	int l;
	int i;
	int top;
	float coef;
	int invert;

	sort_pixels(&start, &stop);
	printf("o-> %i\n", (int)start.x);
	invert = get_lenght_coef(start, stop, &l, &coef);
	mlx_pixel_put(mlx, win, (int)start.x, (int)start.y, (int)start.c);
	mlx_pixel_put(mlx, win, (int)stop.x, (int)stop.y, (int)stop.c);
	i = 0;
	while (i < l)
	{

		//printf("x: %i, y: %i, f: %f\n", (int)(start.x + i),  (int)(((start.x + i) * coef) + start.y + 0.5), coef);
		if (!invert)
			mlx_pixel_put(mlx, win, (int)((float)((float)(i) * coef + 0.5)) + (start.x), (int)(start.y + i), (int)start.c);
		else
			mlx_pixel_put(mlx, win, (int)(start.x + i),  (int)((float)((float)(i) * coef + 0.5)) + (start.y), (int)start.c);
		i++;
	}
}

void	draw2(void *mlx, void *win, t_pixel start, t_pixel stop)
{
	int ex = ft_abs(stop.x - start.x);
	int ey = ft_abs(stop.y - start.y);
	int dx = 2 * ex;
	int dy = 2 * ey;
	int Dx = ex;
	int Dy = ey;
	int i = 0;
	int Xincr = 1;
	int Yincr = 1;

	if (start.x > stop.x)
		Xincr = -1;
	if (start.y > stop.y)
		Yincr = -1;
	printf("test : %i et %i\n", Dx, Dy);
	if (Dx > Dy)
	{
		printf("test\n");
		while (i <= Dx)
		{
			mlx_pixel_put(mlx, win, start.x, start.y, (int)start.c);
			i++;
			start.x += Xincr;
			ex -= dy;
			if (ex < 0)
			{
				start.y += Yincr;
				ex += dx;
			}
		}
	}
	if (Dy > Dx)
	{
		printf("test2\n");
		while (i <= Dy)
		{
			mlx_pixel_put(mlx, win, start.x, start.y, (int)start.c);
			i++;
			start.y += Yincr;
			ey -= dx;
			if (ey < 0)
			{
				start.x += Xincr;
				ey += dy;
			}
		}
	}
}

int		main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 1000, "Coucou mon coco");
	draw2(mlx, win, new_pixel(10, 10), new_pixel(42, 42));
	draw2(mlx, win, new_pixel(10, 10), new_pixel(12, 100));
	draw2(mlx, win, new_pixel(10, 10), new_pixel(25, 100));
	draw2(mlx, win, new_pixel(10, 10), new_pixel(100, 12));
	draw2(mlx, win, new_pixel(10, 10), new_pixel(100, 25));
	draw2(mlx, win, new_pixel(10, 10), new_pixel(100, 20));
	draw2(mlx, win, new_pixel(10, 10), new_pixel(100, 40));
	draw2(mlx, win, new_pixel(10, 10), new_pixel(100, 90));
	draw2(mlx, win, new_pixel(10, 10), new_pixel(500, 95));


	draw2(mlx, win, new_pixel(990-42, 990- 42), new_pixel(990, 990));
	draw2(mlx, win, new_pixel(990-12, 990-100), new_pixel(990, 990));
	draw2(mlx, win, new_pixel(990-25, 990-100), new_pixel(990, 990));
	draw2(mlx, win, new_pixel(900-100, 990- 12), new_pixel(990, 990));
	draw2(mlx, win, new_pixel(900-100, 990- 25), new_pixel(990, 990));

	draw2(mlx, win, new_pixel(990-42, 42), new_pixel(990, 10));
	draw2(mlx, win, new_pixel(990-12, 100), new_pixel(990, 10));
	draw2(mlx, win, new_pixel(990-25, 100), new_pixel(990, 10));
	draw2(mlx, win, new_pixel(900-100, 12), new_pixel(990, 10));
	draw2(mlx, win, new_pixel(900-100, 25), new_pixel(990, 10));

	draw2(mlx, win, new_pixel(42, 990- 42), new_pixel(10, 990));
	draw2(mlx, win, new_pixel(12, 990-100), new_pixel(10, 990));
	draw2(mlx, win, new_pixel(25, 990-100), new_pixel(10, 990));
	draw2(mlx, win, new_pixel(100, 990- 12), new_pixel(10, 990));
	draw2(mlx, win, new_pixel(100, 990- 25), new_pixel(10, 990));

	mlx_loop(mlx);	
}
