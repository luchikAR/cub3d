#include "../cub3d.h"

int	work_r(char *str_map, t_data_game *data_game, int i, int *k)
{
	long	x_width;
	long	y_height;

	ft_init_r(&x_width, &y_height, &i);
	(*k)++;
	while (str_map[i] != '\0' && ft_strchr(" \t", str_map[i]) != 0)
		i++;
	while (str_map[i] != ' ' && str_map[i] != '\0')
	{
		if (!(str_map[i] >= '0' && str_map[i] <= '9'))
			return (-2);
		x_width = x_width * 10 + (str_map[i] - '0');
		i++;
	}
	while (str_map[i] != '\0' && ft_strchr(" \t", str_map[i]) != 0)
		i++;
	while (str_map[i] != '\n' && str_map[i] != '\r' && str_map[i] != '\0')
	{
		if (!(str_map[i] >= '0' && str_map[i] <= '9'))
			return (-1);
		y_height = y_height * 10 + (str_map[i] - '0');
		i++;
	}
	ft_kek(data_game, x_width, y_height);
	return (i);
}

int	work_texstura(char *str_map, char **texture, int i, int *k)
{
	int		j;
	char	*str_data;

	(*k)++;
	i += 2;
	while (str_map[i] != '\0' && ft_strchr(" \t\r", str_map[i]) != 0)
		i++;
	j = i;
	while (str_map[j] != '\n' && str_map[j] != '\r' && str_map[j] != '\0')
		j++;
	str_data = malloc(sizeof(char) * (j - i) + 1);
	if (str_data == NULL)
		return (-2);
	j = 0;
	while (str_map[i] != '\n' && str_map[i] != '\r' && str_map[i] != '\0')
	{
		if (str_map[i] == ' ' || str_map[i] == '\t')
			return (-1);
		str_data[j] = str_map[i++];
		j++;
	}
	str_data[j] = '\0';
	*texture = str_data;
	return (i);
}

int	work_fc(char *str_map, int color[3], int i, int *k)
{
	int	j;

	i++;
	(*k)++;
	j = 0;
	while (j < 3)
		color[j++] = 0;
	j = 0;
	while ((str_map[i] == ' ' || str_map[i] == '\t') && str_map[i] != '\0')
		i++;
	while (j < 3 && str_map[i] != '\0' && str_map[i] != '\r' && str_map[i] != '\n')
	{
		if (!(str_map[i] >= '0' && str_map[i] <= '9') && str_map[i] != ',')
			return (-2);
		color[j] = color[j] * 10 + (str_map[i] - '0');
		i++;
		if (str_map[i] == ',')
		{
			j++;
			i++;
		}
	}
	return (i);
}

int	help_p_one(char *str_map, t_data_game *data_game, int i, int *k)
{
	if (str_map[i] == 'R')
		i = work_r(str_map, data_game, i, k);
	else if (str_map[i] == 'N' && str_map[i + 1] == 'O')
		i = work_texstura(str_map, &data_game->no_texture, i, k);
	else if (str_map[i] == 'S' && str_map[i + 1] == 'O')
		i = work_texstura(str_map, &data_game->so_texture, i, k);
	else if (str_map[i] == 'W' && str_map[i + 1] == 'E')
		i = work_texstura(str_map, &data_game->we_texture, i, k);
	else if (str_map[i] == 'E' && str_map[i + 1] == 'A')
		i = work_texstura(str_map, &data_game->ea_texture, i, k);
	else if (str_map[i] == 'S')
		i = work_texstura(str_map, &data_game->s_texture, i, k);
	else if (str_map[i] == 'F')
		i = work_fc(str_map, data_game->f_color, i, k);
	else if (str_map[i] == 'C')
		i = work_fc(str_map, data_game->c_color, i, k);
	return (i);
}

int	valid_part_one(char *str_map, t_data_game *data_game)
{
	int	k;
	int	i;

	i = 0;
	k = 0;
	while (k != 8 && str_map[i] != '\0' && i != -1)
	{
		while (str_map[i] != '\0' && ft_strchr(" \n\t", str_map[i]) != 0)
			i++;
		i = help_p_one(str_map, data_game, i, &k);
		i++;
	}
	if (i == -1 || k != 8)
		return (-1);
	return (i);
}
