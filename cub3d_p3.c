#include "cub3d.h"

void	ft_init_conf(t_data_game *data_game)
{
	data_game->conf.buf = NULL;
	data_game->conf.zBuffer = NULL;
	data_game->conf.moveSpeed = 0.05;
	data_game->conf.rotSpeed = 0.05;
	data_game->conf.key_a = 0;
	data_game->conf.key_w = 0;
	data_game->conf.key_s = 0;
	data_game->conf.key_d = 0;
	data_game->conf.key_esc = 0;
}

int	ft_malloc_tex(t_data_game *data_game, int i, int j)
{
	data_game->conf.texture = (int **)malloc(sizeof(int *) * 5);
	if (data_game->conf.texture == NULL)
		return (-1);
	i = 0;
	while (i < 5)
	{
		data_game->conf.texture[i] = (int *)malloc(sizeof(int) \
			* (TEX_HEIGHT * TEX_WIDTH));
		if (data_game->conf.texture[i] == NULL)
			return (-1);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < TEX_HEIGHT * TEX_WIDTH)
		{
			data_game->conf.texture[i][j] = 0;
			j++;
		}
		i++;
	}
	return (1);
}
