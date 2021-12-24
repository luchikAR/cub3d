#include "../cub3d.h"

void	sprite_init(t_data_game *d_g, t_sp_help *h, int i)
{
	h->invDet = 1.0 / (d_g->conf.planeX * d_g->conf.dirY - d_g->conf.dirX \
		* d_g->conf.planeY);
	h->transformX = h->invDet * (d_g->conf.dirY * h->spriteX - \
		d_g->conf.dirX * h->spriteY);
	h->transformY = h->invDet * (-d_g->conf.planeY * h->spriteX + \
		d_g->conf.planeX * h->spriteY);
	h->spriteScreenX = (int)((d_g->x_width / 2) * (1 + h->transformX \
		/ h->transformY));
	h->vMoveScreen = (int)(V_MOVE / h->transformY);
	h->spriteHeight = (int)fabs((d_g->y_height / h->transformY) / V_DIV);
	h->drawStartY = -h->spriteHeight / 2 + d_g->y_height / 2 + h->vMoveScreen;
	if (h->drawStartY < 0)
		h->drawStartY = 0;
	h->drawEndY = h->spriteHeight / 2 + d_g->y_height / 2 + h->vMoveScreen;
	if (h->drawEndY >= d_g->y_height)
		h->drawEndY = d_g->y_height - 1;
	h->spriteWidth = (int)fabs((d_g->y_height / h->transformY) / U_DIV);
	h->drawStartX = -h->spriteWidth / 2 + h->spriteScreenX;
	if (h->drawStartX < 0)
		h->drawStartX = 0;
	h->drawEndX = h->spriteWidth / 2 + h->spriteScreenX;
	if (h->drawEndX >= d_g->x_width)
		h->drawEndX = d_g->x_width - 1;
}

void	help_spr_drow(t_data_game *d_g, t_sp_help *help, int y, int stripe)
{
	int	texY;

	help->d = (y - help->vMoveScreen) * 256 - d_g->y_height * \
		128 + help->spriteHeight * 128;
	texY = ((help->d * TEX_HEIGHT) / help->spriteHeight) / 256;
	help->color = d_g->conf.texture[4][TEX_WIDTH * texY + help->texX];
	if ((help->color & 0x00FFFFFF) != 0)
		d_g->conf.buf[y][stripe] = help->color;
}

void	sprite_drow(t_data_game *d_g, t_sp_help *help)
{
	int	stripe;
	int	y;

	stripe = help->drawStartX;
	while (stripe < help->drawEndX)
	{
		y = help->drawStartY;
		help->texX = (int)((256 * (stripe - (-help->spriteWidth / 2 + \
			help->spriteScreenX)) * TEX_WIDTH / help->spriteWidth) / 256);
		if (help->transformY > 0 && stripe > 0 && stripe < d_g->x_width \
			&& help->transformY < d_g->conf.zBuffer[stripe])
		{
			while (y < help->drawEndY)
			{
				help_spr_drow(d_g, help, y, stripe);
				y++;
			}
		}
		stripe++;
	}
}

void	wall_casting_sprite(t_data_game *d_g)
{
	int			i;
	t_sp_help	help;

	ft_mal_sprite(d_g, &help);
	i = 0;
	while (i < d_g->count_sprite)
	{
		help.spriteOrder[i] = i;
		help.spriteDistance[i] = ((d_g->conf.posX - d_g->sprite[i].x) * \
			(d_g->conf.posX - d_g->sprite[i].x) + (d_g->conf.posY \
			- d_g->sprite[i].y) * (d_g->conf.posY - d_g->sprite[i].y));
		i++;
	}
	sortSprites(help.spriteOrder, help.spriteDistance, d_g->count_sprite);
	i = 0;
	while (i < d_g->count_sprite)
	{
		help.spriteX = d_g->sprite[help.spriteOrder[i]].x - d_g->conf.posX;
		help.spriteY = d_g->sprite[help.spriteOrder[i]].y - d_g->conf.posY;
		sprite_init(d_g, &help, i);
		sprite_drow(d_g, &help);
		i++;
	}
	free(help.spriteDistance);
	free(help.spriteOrder);
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	i = 0;
	sprites = (t_pair *)malloc(sizeof(t_pair) * amount);
	if (sprites == NULL)
		return ;
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	i = 0;
	sort_order(sprites, amount);
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}
