#include "../cub3d.h"

void	ft_were_p_help(t_data_game *data_game, int i, int j)
{
	if (data_game->str_map[i][j] == 'N')
	{
		data_game->conf.dirX = 0;
		data_game->conf.dirY = -1;
		data_game->conf.planeX = -0.66;
		data_game->conf.planeY = 0;
	}
	if (data_game->str_map[i][j] == 'S')
	{
		data_game->conf.dirX = 0;
		data_game->conf.dirY = 1;
		data_game->conf.planeX = 0.66;
		data_game->conf.planeY = 0;
	}
}

void	ft_were_player(t_data_game *data_game, int i, int j)
{
	ft_were_p_help(data_game, i, j);
	if (data_game->str_map[i][j] == 'W')
	{
		data_game->conf.dirX = 1;
		data_game->conf.dirY = 0;
		data_game->conf.planeX = 0;
		data_game->conf.planeY = -0.66;
	}
	if (data_game->str_map[i][j] == 'E')
	{
		data_game->conf.dirX = -1;
		data_game->conf.dirY = 0;
		data_game->conf.planeX = 0;
		data_game->conf.planeY = 0.66;
	}
	if (ft_strchr("NSWE", data_game->str_map[i][j]) != 0)
	{
		data_game->str_map[i][j] = '0';
		data_game->conf.posX = (double)i + 0.5;
		data_game->conf.posY = (double)j + 0.5;
	}
}

int	ft_probel(char **str_map, t_data_game *data_game)
{
	int	stroka;
	int	stolbez;

	stolbez = 0;
	stroka = 0;
	while (str_map[stroka] != NULL)
	{
		while (str_map[stroka][stolbez] != '\0')
		{
			ft_were_player(data_game, stroka, stolbez);
			if (ft_probel2(str_map, stroka, stolbez) == -1)
				return (-1);
			stolbez++;
		}
		stroka++;
		stolbez = 0;
	}
	return (1);
}

int	ft_probel2(char **str_map, int stroka, int stolbez)
{
	if (str_map[stroka][stolbez] == ' ')
	{
		if ((stroka > 0 && (int)ft_strlen(str_map[stroka - 1]) >= stolbez) \
			&& (str_map[stroka - 1][stolbez] != '1' && \
			str_map[stroka - 1][stolbez] != ' '))
			return (-1);
		else if ((str_map[stroka + 1] != NULL && (int)ft_strlen(str_map[stroka + 1]) \
			>= stolbez) && (str_map[stroka + 1][stolbez] != '1' && \
			str_map[stroka + 1][stolbez] != ' '))
			return (-1);
		else if (stolbez > 0 \
				&& (str_map[stroka][stolbez - 1] != '1' && \
				str_map[stroka][stolbez - 1] != ' '))
			return (-1);
		else if ((str_map[stroka][stolbez + 1] != '\0') \
				&& (str_map[stroka][stolbez + 1] != '1' && \
				str_map[stroka][stolbez + 1] != ' '))
			return (-1);
		else
			stolbez = stolbez;
	}
	return (1);
}

void	ft_kek(t_data_game *data_game, long x_width, long y_height)
{
	if (x_width < 100)
		x_width = 100;
	if (y_height < 100)
		y_height = 100;
	if (x_width > 2560)
		x_width = 2560;
	if (y_height > 1440)
		y_height = 1440;
	data_game->x_width = x_width;
	data_game->y_height = y_height;
}
