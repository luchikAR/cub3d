#include "../cub3d.h"

char	**ft_malloc_map(char *str_map, int i)
{
	int		k;
	int		flag;
	char	**res;

	k = 0;
	flag = 0;
	while (str_map[i] != '\0')
	{
		if (ft_strchr("NSWE", str_map[i]) != 0)
			flag++;
		if (str_map[i] == '\n')
			k++;
		i++;
	}
	res = malloc((int)(sizeof(char *)) *(k + 2));
	if (res == NULL)
		return (NULL);
	res[k + 1] = NULL;
	if (flag != 1)
		return (NULL);
	return (res);
}

int	ft_malloc_str(t_data_game *data_game, char *str_map, int i)
{
	int	k;
	int	j;

	j = 0;
	k = 0;
	while (str_map[i] != '\0')
	{
		if (ft_strchr(" 012\n\rNSWE", str_map[i]) == 0)
			return (-1);
		j++;
		if (str_map[i] == '\n')
		{
			data_game->str_map[k] = malloc(j + 1);
			if (data_game->str_map[k] == NULL)
				return (-1);
			j = 0;
			k++;
		}
		i++;
	}
	data_game->str_map[k] = malloc(j + 1);
	if (k < 3)
		return (-1);
	return (1);
}

int	ft_up_down(char **str_map)
{
	int	stroka;
	int	stolbez;

	stolbez = 0;
	stroka = 0;
	while (str_map[stroka] != NULL)
		stroka++;
	stroka--;
	while (str_map[stroka][stolbez] != '\0')
	{
		if (str_map[stroka][stolbez] != '1' && str_map[stroka][stolbez] != ' ')
			return (-1);
		stolbez++;
	}
	stolbez = 0;
	while (str_map[0][stolbez] != '\0')
	{
		if (ft_strchr("1 \r", str_map[0][stolbez]) == 0)
			return (-1);
		stolbez++;
	}
	return (1);
}

int	ft_right_help(char **str_map, int stroka)
{
	int	i;

	i = 0;
	while (ft_strlen(str_map[stroka + 1]) <= ft_strlen(str_map[stroka]) - i)
	{
		i++;
		if (ft_strchr("1\r", str_map[stroka][ft_strlen(str_map[stroka]) \
			- i]) == 0)
			return (-1);
	}
	return (1);
}

int	ft_left_right(char **str_map)
{
	int	stroka;
	int	stolbez;

	stolbez = 0;
	stroka = 0;
	while (str_map[stroka] != NULL)
	{
		while (str_map[stroka][stolbez] == ' ')
			stolbez++;
		if (str_map[stroka][stolbez] != '1')
			return (-1);
		if (ft_strchr("1\r", str_map[stroka][ft_strlen(str_map[stroka]) \
			- 1]) == 0)
			return (-1);
		if ((str_map[stroka + 1] != NULL) && (ft_strlen(str_map[stroka \
			+ 1]) <= ft_strlen(str_map[stroka])))
			if (ft_right_help(str_map, stroka) == -1)
				return (-1);
		stolbez = 0;
		stroka++;
	}
	return (1);
}
