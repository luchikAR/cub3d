#ifndef CUB3D_P2_H
# define CUB3D_P2_H

# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define K_A 0
# define K_D 2
# define K_S 1
# define K_W 13
# define K_AR_L 123
# define K_AR_R 124
# define K_AR_U 126
# define K_AR_D 125
# define K_ESC 53
# define U_DIV 1
# define V_DIV 1
# define V_MOVE 0.0

typedef struct s_sprite
{
	double		x;
	double		y;
}					t_sprite;

typedef struct s_sp_help
{
	double	spriteX;
	double	spriteY;
	double	invDet;
	double	transformX;
	double	transformY;
	int		spriteScreenX;
	int		vMoveScreen;
	int		spriteHeight;
	int		drawStartY;
	int		drawEndY;
	int		spriteWidth;
	int		drawStartX;
	int		drawEndX;
	int		texX;
	int		color;
	int		d;
	int		*spriteOrder;
	double	*spriteDistance;
}					t_sp_help;

typedef struct s_pair
{
	double	first;
	int		second;
}					t_pair;

typedef struct s_floor
{
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	float	posZ;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
	int		p;
}					t_floor;

typedef struct s_wall
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;	
	double	step;
	double	texPos;
	double	wallX;	
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		texNum;
	int		texX;
}					t_wall;

#endif