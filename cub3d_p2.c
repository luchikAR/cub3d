#include "cub3d.h"

void	ft_free(t_data_game *data_game)
{
	int	i;

	i = 0;
	if (data_game->no_texture != NULL)
		free(data_game->no_texture);
	if (data_game->so_texture != NULL)
		free(data_game->so_texture);
	if (data_game->we_texture != NULL)
		free(data_game->we_texture);
	if (data_game->ea_texture != NULL)
		free(data_game->ea_texture);
	if (data_game->s_texture != NULL)
		free(data_game->s_texture);
}

int 	exit_error(char *error, t_data_game *data_game)
{
	if (error)
	{
		write(2, "Error: ", 7);
		write(2, error, ft_strlen(error));
		write(2, "\n", 1);
	}
	ft_free(data_game);
	return (-1);
}

int	ft_malloc_buf(t_data_game *data_game)
{
	int	i;

	i = 0;
	data_game->conf.buf = (int **)malloc(sizeof(int *) * data_game->y_height);
	if (data_game->conf.buf == NULL)
		return (-1);
	while (i < data_game->y_height)
	{
		data_game->conf.buf[i] = malloc(sizeof(int) * data_game->x_width);
		if (data_game->conf.buf[i] == NULL)
			return (-1);
		i++;
	}
	data_game->conf.zBuffer = (double *)malloc(sizeof(double) * \
		data_game->x_width);
	if (data_game->conf.zBuffer == NULL)
		return (-1);
	return (1);
}

int	ft_inc(t_data_game *data_game, int i, int j)
{
	if (ft_malloc_buf(data_game) == -1)
		return (-1);
	i = 0;
	while (i < data_game->y_height)
	{
		j = 0;
		while (j < data_game->x_width)
		{
			data_game->conf.buf[i][j] = 0;
			j++;
		}
		i++;
	}
	ft_malloc_tex(data_game, 0, 0);
	return (1);
}
