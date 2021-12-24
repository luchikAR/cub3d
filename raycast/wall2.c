#include "../cub3d.h"

void	ft_init_wall(t_data_game *data_game, t_wall *wall, int x)
{
	wall->cameraX = 2 * x / (double)data_game->x_width - 1;
	wall->rayDirX = data_game->conf.dirX + data_game->conf.planeX \
		* wall->cameraX;
	wall->rayDirY = data_game->conf.dirY + data_game->conf.planeY \
		* wall->cameraX;
	wall->mapX = (int)data_game->conf.posX;
	wall->mapY = (int)data_game->conf.posY;
	wall->deltaDistX = fabs(1 / wall->rayDirX);
	wall->deltaDistY = fabs(1 / wall->rayDirY);
}

void	ft_init_stap(t_data_game *data_game, t_wall *wall)
{
	wall->hit = 0;
	if (wall->rayDirX < 0)
	{
		wall->stepX = -1;
		wall->sideDistX = (data_game->conf.posX - wall->mapX) \
			* wall->deltaDistX;
	}
	else
	{
		wall->stepX = 1;
		wall->sideDistX = (wall->mapX + 1.0 - data_game->conf.posX) \
			* wall->deltaDistX;
	}
	if (wall->rayDirY < 0)
	{
		wall->stepY = -1;
		wall->sideDistY = (data_game->conf.posY - wall->mapY) \
			* wall->deltaDistY;
	}
	else
	{
		wall->stepY = 1;
		wall->sideDistY = (wall->mapY + 1.0 - data_game->conf.posY) \
			* wall->deltaDistY;
	}
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	ft_mal_sprite(t_data_game *d_g, t_sp_help *help)
{
	help->spriteOrder = malloc(sizeof(int) * d_g->count_sprite);
	if (help->spriteOrder == NULL)
		return ;
	help->spriteDistance = malloc(sizeof(double) * d_g->count_sprite);
	if (help->spriteDistance == NULL)
		return ;
}
