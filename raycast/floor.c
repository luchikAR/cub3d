#include "../cub3d.h"

void	ft_floor_calc(t_data_game *data_game, t_floor *floor, int y)
{
	floor->rayDirX0 = data_game->conf.dirX - data_game->conf.planeX;
	floor->rayDirY0 = data_game->conf.dirY - data_game->conf.planeY;
	floor->rayDirX1 = data_game->conf.dirX + data_game->conf.planeX;
	floor->rayDirY1 = data_game->conf.dirY + data_game->conf.planeY;
	floor->p = y - data_game->y_height / 2;
	floor->posZ = 0.5 * data_game->y_height;
	floor->rowDistance = floor->posZ / floor->p;
	floor->floorStepX = floor->rowDistance * (floor->rayDirX1 - \
		floor->rayDirX0) / data_game->x_width;
	floor->floorStepY = floor->rowDistance * (floor->rayDirY1 - \
		floor->rayDirY0) / data_game->x_width;
	floor->floorX = data_game->conf.posX + floor->rowDistance * floor->rayDirX0;
	floor->floorY = data_game->conf.posY + floor->rowDistance * floor->rayDirY0;
}

void	ft_floor_drow(t_data_game *data_game, t_floor *floor, int y, int x)
{
	int	cellX;
	int	cellY;
	int	tx;
	int	ty;
	int	color;

	cellX = (int)(floor->floorX);
	cellY = (int)(floor->floorY);
	tx = (int)(TEX_WIDTH * (floor->floorX - cellX)) & (TEX_WIDTH - 1);
	ty = (int)(TEX_HEIGHT * (floor->floorY - cellY)) & (TEX_HEIGHT - 1);
	floor->floorX += floor->floorStepX;
	floor->floorY += floor->floorStepY;
	color = data_game->f_color[0] * 256 * 256 + data_game->f_color[1] * 256 \
		+ data_game->f_color[2];
	color = (color >> 1) & 8355711;
	data_game->conf.buf[y][x] = color;
	color = data_game->c_color[0] * 256 * 256 + data_game->c_color[1] * 256 \
		+ data_game->c_color[2];
	color = (color >> 1) & 8355711;
	data_game->conf.buf[data_game->y_height - y - 1][x] = color;
}

void	floor_casting(t_data_game *data_game)
{
	int		y;
	int		x;
	t_floor	floor;

	y = data_game->y_height / 2 + 1;
	while (y < data_game->y_height)
	{
		ft_floor_calc(data_game, &floor, y);
		x = 0;
		while (x < data_game->x_width)
		{
			ft_floor_drow(data_game, &floor, y, x);
			x++;
		}
		y++;
	}
}
