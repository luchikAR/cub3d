#include "../cub3d.h"

int	valid_file(char *str_all_file, t_data_game *data_game)
{
	int	i;

	i = valid_part_one(str_all_file, data_game);
	if (i == -1)
	{
		data_game->error = "Not valid parameters :)";
		return (-1);
	}
	if (valid_part_two(str_all_file, data_game, i) == -1)
	{
		data_game->error = "Not valid map :)";
		return (-1);
	}
	return (1);
}

int	read_file(int fd, char **str_all_file)
{
	int		len;
	char	buffer[65];

	len = read(fd, buffer, 64);
	while (len > 0)
	{
		buffer[len] = '\0';
		*str_all_file = ft_strjoin(*str_all_file, buffer);
		len = read(fd, buffer, 64);
	}
	close(fd);
	if (len == -1)
		return (len);
	return (1);
}

int	chek_map(int fd, t_data_game *data_game)
{
	char	*str_all_file;
	int		error;

	str_all_file = NULL;
	error = read_file(fd, &str_all_file);
	if (error < 0)
	{
		free(str_all_file);
		data_game->error = strerror(errno);
		return (-1);
	}
	if (valid_file(str_all_file, data_game) == -1)
	{
		free(str_all_file);
		return (-1);
	}
	free(str_all_file);
	return (1);
}
