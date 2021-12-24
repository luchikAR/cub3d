#include "../cub3d.h"

int	ft_chek_valid(char **str_map, t_data_game *data_game)
{
	if (ft_up_down(str_map) == -1)
		return (-1);
	if (ft_left_right(str_map) == -1)
		return (-1);
	if (ft_probel(str_map, data_game) == -1)
		return (-1);
	return (1);
}

int	ft_sprite_help(t_data_game *data_game, int i, int j)
{
	while (data_game->str_map[i] != NULL)
	{
		while (data_game->str_map[i][j] != '\0')
		{
			if (data_game->str_map[i][j] - '0' == 2)
				data_game->count_sprite++;
			j++;
		}
		j = 0;
		i++;
	}
	data_game->sprite = malloc((sizeof(t_sprite) * data_game->count_sprite));
	if (data_game->sprite == NULL)
		return (-1);
	return (1);
}

int	ft_sprite_init(t_data_game *data_game, int i, int j)
{
	int	k;

	k = 0;
	data_game->count_sprite = 0;
	if (ft_sprite_help(data_game, 0, 0) == -1)
		return (-1);
	while (data_game->str_map[i] != NULL)
	{
		while (data_game->str_map[i][j] != '\0')
		{
			if (data_game->str_map[i][j] == '2')
			{
				data_game->str_map[i][j] = '0';
				data_game->sprite[k].x = i + 0.5;
				data_game->sprite[k].y = j + 0.5;
				k++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	ft_valid_help(char *str_all_file, t_data_game *data_game, int i, int k)
{
	int	j;

	j = 0;
	while (str_all_file[i] != '\0')
	{
		if (str_all_file[i] == '\n')
		{
			data_game->str_map[k][j] = '\0';
			j = 0;
			k++;
			i++;
		}
		data_game->str_map[k][j] = str_all_file[i];
		j++;
		i++;
	}
	data_game->str_map[k][j] = '\0';
}

int	valid_part_two(char *str_all_file, t_data_game *data_game, int i)
{
	int	k;

	k = 0;
	while (str_all_file[i] == '\n' || str_all_file[i] == '\r')
		i++;
	data_game->str_map = ft_malloc_map(str_all_file, i);
	if (data_game->str_map == NULL)
		return (-1);
	if (ft_malloc_str(data_game, str_all_file, i) == -1)
		return (-1);
	ft_valid_help(str_all_file, data_game, i, k);
	if (ft_sprite_init(data_game, 0, 0) == -1)
		return (-1);
	return (ft_chek_valid(data_game->str_map, data_game));
}
