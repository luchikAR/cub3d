#include "cub3d.h"

int	load_image(t_conf *conf, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	y = 0;
	img->img_width = 64;
	img->img_height = 64;
	img->img = mlx_xpm_file_to_image(conf->init_mlx, (char *)(path), \
		&img->img_width, &img->img_height);
	if (img->img == NULL)
		return (-1);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, \
		&img->size_l, &img->endian);
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(conf->init_mlx, img->img);
	return (0);
}

int	load_texture(t_data_game *d_g)
{
	t_img	img;
	int		i;

	i = 0;
	i += load_image(&d_g->conf, d_g->conf.texture[0], d_g->no_texture, &img);
	i += load_image(&d_g->conf, d_g->conf.texture[1], d_g->so_texture, &img);
	i += load_image(&d_g->conf, d_g->conf.texture[2], d_g->we_texture, &img);
	i += load_image(&d_g->conf, d_g->conf.texture[3], d_g->ea_texture, &img);
	i += load_image(&d_g->conf, d_g->conf.texture[4], d_g->s_texture, &img);
	return (i);
}

int	ft_check_param(int argc, char *argv[], t_data_game *data_game, int *fd)
{
	data_game->conf.buf = NULL;
	if (argc < 2 || argc > 3 || (argc == 3 && ft_strcmp(argv[2], "--save")))
		return (exit_error("not valid argument", data_game));
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		data_game->flag = 1;
	else
		data_game->flag = 0;
	if (!(argv[1][ft_strlen(argv[1]) - 1] == 'b' && argv[1][ft_strlen(argv[1]) - 2] == 'u' \
		&& argv[1][ft_strlen(argv[1]) - 3] == 'c' \
		&& argv[1][ft_strlen(argv[1]) - 4] == '.'))
		return (exit_error("Не верное разрешение файла (.cub)", data_game));
	(*fd) = open(argv[1], O_RDONLY);
	if ((*fd) < 0)
		return (exit_error("Подаётся не существующий файл", data_game));
	return (1);
}

void	ft_help_main(t_data_game *data_game)
{
	data_game->conf.win = mlx_new_window(data_game->conf.init_mlx, data_game->x_width, data_game->y_height, \
		"cub3D");
	data_game->conf.img.img = mlx_new_image(data_game->conf.init_mlx, data_game->x_width, \
		data_game->y_height);
	data_game->conf.img.data = (int *)mlx_get_data_addr(data_game->conf.img.img, &data_game->conf.img.bpp, \
			&data_game->conf.img.size_l, &data_game->conf.img.endian);
	mlx_loop_hook(data_game->conf.init_mlx, &main_loop, data_game);
	mlx_hook(data_game->conf.win, 2, 0, &key_press, data_game);
	mlx_hook(data_game->conf.win, 3, 0, &key_release, data_game);
	mlx_hook(data_game->conf.win, 17, 0, &end_game, data_game);
	mlx_loop(data_game->conf.init_mlx);
}

int	main(int argc, char *argv[])
{
	t_data_game	data_game;
	int			fd;

	if (ft_check_param(argc, argv, &data_game, &fd) == -1)
		return (-1);
	if (chek_map(fd, &data_game) == -1)
		return (exit_error(data_game.error, &data_game));
	data_game.conf.init_mlx = mlx_init();
	if (data_game.conf.init_mlx == NULL)
		return (exit_error("Не удалось установить соединение", &data_game));
	ft_init_conf(&data_game);
	if (ft_inc(&data_game, 0, 0) == -1)
		return (-1);
	if (load_texture(&data_game) < 0)
		return (exit_error("Не удалось найти текстуру", &data_game));
	ft_help_main(&data_game);
	ft_free(&data_game);
	return (1);
}
