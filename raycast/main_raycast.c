#include "../cub3d.h"

int	main_loop(t_data_game *data_game)
{
	calc(data_game);
	if (data_game->flag == 1)
		return (screenshot(data_game));
	draw(data_game);
	key_update(data_game, &data_game->conf);
	return (0);
}

void	calc(t_data_game *data_game)
{
	floor_casting(data_game);
	wall_casting(data_game);
	wall_casting_sprite(data_game);
}

void	draw(t_data_game *data_game)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y < data_game->y_height)
	{
		x = 0;
		while (x < data_game->x_width)
		{
			data_game->conf.img.data[y * data_game->x_width + x] = \
				data_game->conf.buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data_game->conf.init_mlx, data_game->conf.win, \
		data_game->conf.img.img, 0, 0);
}

void	screenshot2(int fd, t_data_game *d_g)
{
	int32_t	x;
	int32_t	y;

	y = d_g->y_height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < d_g->x_width)
		{
			write(fd, &d_g->conf.buf[y][x], 4);
			x++;
		}
		y--;
	}
	close(fd);
	exit(0);
}

int	screenshot(t_data_game *d_g)
{
	int		fd;
	char	bitmap[54];

	fd = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (fd < 0)
	{
		write(2, "Error: Сreating a screenshot resulted in an error\n", 50);
		exit(-1);
	}
	ft_bzero(bitmap, 54);
	bitmap[0] = 'B';
	bitmap[1] = 'M';
	*((int *)(bitmap + 2)) = d_g->y_height * d_g->x_width * 4 + 54;
	*(int *)(bitmap + 10) = 54;
	*(int *)(bitmap + 14) = 40;
	*(int *)(bitmap + 18) = d_g->x_width;
	*(int *)(bitmap + 22) = d_g->y_height;
	*(bitmap + 26) = 1;
	*(bitmap + 28) = 32;
	write(fd, bitmap, 54);
	screenshot2(fd, d_g);
	return (1);
}
