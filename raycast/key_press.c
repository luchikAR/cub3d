#include "../cub3d.h"

int	end_game(t_data_game *data_game)
{
	if (data_game->conf.init_mlx)
		mlx_destroy_window(data_game->conf.init_mlx, data_game->conf.win);
	exit(0);
	return (0);
}

int	key_press(int key, t_data_game *data_game)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W || key == K_AR_U)
		data_game->conf.key_w = 1;
	else if (key == K_A || key == K_AR_L)
		data_game->conf.key_a = 1;
	else if (key == K_S || key == K_AR_D)
		data_game->conf.key_s = 1;
	else if (key == K_D || key == K_AR_R)
		data_game->conf.key_d = 1;
	return (0);
}

int	key_release(int key, t_data_game *data_game)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W || key == K_AR_U)
		data_game->conf.key_w = 0;
	else if (key == K_A || key == K_AR_L)
		data_game->conf.key_a = 0;
	else if (key == K_S || key == K_AR_D)
		data_game->conf.key_s = 0;
	else if (key == K_D || key == K_AR_R)
		data_game->conf.key_d = 0;
	return (0);
}

void	key_update_p2(t_data_game *data_game, t_conf *c)
{
	double	oldDirX;
	double	oldPlaneX;

	if (c->key_d)
	{
		oldDirX = c->dirX;
		c->dirX = c->dirX * cos(-c->rotSpeed) - c->dirY * sin(-c->rotSpeed);
		c->dirY = oldDirX * sin(-c->rotSpeed) + c->dirY * cos(-c->rotSpeed);
		oldPlaneX = c->planeX;
		c->planeX = c->planeX * cos(-c->rotSpeed) - c->planeY * \
			sin(-c->rotSpeed);
		c->planeY = oldPlaneX * sin(-c->rotSpeed) + c->planeY * \
			cos(-c->rotSpeed);
	}
	if (c->key_a)
	{
		oldDirX = c->dirX;
		c->dirX = c->dirX * cos(c->rotSpeed) - c->dirY * sin(c->rotSpeed);
		c->dirY = oldDirX * sin(c->rotSpeed) + c->dirY * cos(c->rotSpeed);
		oldPlaneX = c->planeX;
		c->planeX = c->planeX * cos(c->rotSpeed) - c->planeY * sin(c->rotSpeed);
		c->planeY = oldPlaneX * sin(c->rotSpeed) + c->planeY * cos(c->rotSpeed);
	}
	if (c->key_esc)
		exit(0);
}

void	key_update(t_data_game *data_game, t_conf *conf)
{
	if (conf->key_w)
	{
		if (!(data_game->str_map[(int)(conf->posX + conf->dirX * \
			conf->moveSpeed)][(int)(conf->posY)] - '0'))
			conf->posX += conf->dirX * conf->moveSpeed;
		if (!(data_game->str_map[(int)(conf->posX)][(int)(conf->posY + \
			conf->dirY * conf->moveSpeed)] - '0'))
			conf->posY += conf->dirY * conf->moveSpeed;
	}
	if (conf->key_s)
	{
		if (!(data_game->str_map[(int)(conf->posX - conf->dirX * \
			conf->moveSpeed)][(int)(conf->posY)] - '0'))
			conf->posX -= conf->dirX * conf->moveSpeed;
		if (!(data_game->str_map[(int)(conf->posX)][(int)(conf->posY - conf->dirY \
			* conf->moveSpeed)] - '0'))
			conf->posY -= conf->dirY * conf->moveSpeed;
	}
	key_update_p2(data_game, conf);
}
