#include "../cub3d.h"

void	ft_DDA(t_data_game *data_game, t_wall *wall)
{
	while (wall->hit == 0)
	{
		if (wall->sideDistX < wall->sideDistY)
		{
			wall->sideDistX += wall->deltaDistX;
			wall->mapX += wall->stepX;
			wall->side = 0;
		}
		else
		{
			wall->sideDistY += wall->deltaDistY;
			wall->mapY += wall->stepY;
			wall->side = 1;
		}
		if ((data_game->str_map[wall->mapX][wall->mapY] - '0') > 0)
			wall->hit = 1;
	}
	if (wall->side == 0)
		wall->perpWallDist = (wall->mapX - data_game->conf.posX \
			+ (1 - wall->stepX) / 2) / wall->rayDirX;
	else
		wall->perpWallDist = (wall->mapY - data_game->conf.posY \
			+ (1 - wall->stepY) / 2) / wall->rayDirY;
}

void	ft_calc_stripe(t_data_game *data_game, t_wall *wall)
{
	wall->lineHeight = (int)(data_game->y_height / wall->perpWallDist);
	wall->drawStart = -wall->lineHeight / 2 + data_game->y_height / 2;
	if (wall->drawStart < 0)
		wall->drawStart = 0;
	wall->drawEnd = wall->lineHeight / 2 + data_game->y_height / 2;
	if (wall->drawEnd >= data_game->y_height)
		wall->drawEnd = data_game->y_height - 1;
}

void	ft_drow_wall(t_data_game *data_game, t_wall *wall)
{
	if (wall->side == 0)
	{
		wall->texNum = 2;
		if (wall->rayDirX > 0)
			wall->texNum = 3;
		wall->wallX = data_game->conf.posY + wall->perpWallDist * wall->rayDirY;
	}
	else
	{
		wall->texNum = 1;
		if (wall->rayDirY > 0)
			wall->texNum = 0;
		wall->wallX = data_game->conf.posX + wall->perpWallDist * wall->rayDirX;
	}
	wall->wallX -= floor((wall->wallX));
	wall->texX = (int)(wall->wallX * (double)TEX_WIDTH);
	if (wall->side == 0 && wall->rayDirX > 0)
		wall->texX = TEX_WIDTH - wall->texX - 1;
	if (wall->side == 1 && wall->rayDirY < 0)
		wall->texX = TEX_WIDTH - wall->texX - 1;
	wall->step = 1.0 * TEX_HEIGHT / wall->lineHeight;
	wall->texPos = (wall->drawStart - data_game->y_height / 2 + wall->lineHeight / 2) \
		* wall->step;
}

void	ft_drow_wall2(t_data_game *data_game, t_wall *wall, int x, int y)
{
	int	texY;
	int	color;

	texY = (int)wall->texPos & (TEX_HEIGHT - 1);
	wall->texPos += wall->step;
	color = data_game->conf.texture[wall->texNum][TEX_HEIGHT \
		* texY + wall->texX];
	if (wall->side == 1)
		color = (color >> 1) & 8355711;
	data_game->conf.buf[y][x] = color;
}

void	wall_casting(t_data_game *data_game)
{
	int		x;
	int		y;
	t_wall	wall;
	int		p;
	int		o;

	x = 0;
	while (x < data_game->x_width)
	{
		ft_init_wall(data_game, &wall, x);
		ft_init_stap(data_game, &wall);
		ft_DDA(data_game, &wall);
		ft_calc_stripe(data_game, &wall);
		ft_drow_wall(data_game, &wall);
		y = wall.drawStart;
		while (y < wall.drawEnd)
		{
			ft_drow_wall2(data_game, &wall, x, y);
			y++;
		}
		data_game->conf.zBuffer[x] = wall.perpWallDist;
		x++;
	}
}
