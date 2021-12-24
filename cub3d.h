#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_p2.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_conf
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	moveSpeed;
	double	rotSpeed;
	void	*init_mlx;
	void	*win;
	t_img	img;
	int		**buf;
	double	*zBuffer;
	int		**texture;
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_esc;
}				t_conf;

typedef struct s_data_game
{
	int			x_width;
	int			y_height;
	int			flag;
	int			f_color[3];
	int			c_color[3];
	char		*error;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*s_texture;
	char		**str_map;
	t_sprite	*sprite;
	int			count_sprite;
	t_conf		conf;
}				t_data_game;

void	*ft_bzero(void *s, size_t n);
int		exit_error(char *error, t_data_game *data_game);
int		chek_map(int fd, t_data_game *data_game);
int		ft_strcmp(char *s1, char *s2);
int		read_file(int fd, char **str_all_file);
int		valid_part_one(char *str_map, t_data_game *data_game);
int		valid_part_two(char *str_all_file, t_data_game *data_game, int i);
int		work_r(char *str_map, t_data_game *data, int i, int *k);
int		ft_up_down(char **str_map);
int		ft_left_right(char **str_map);
int		ft_probel(char **str_map, t_data_game *data_game);
int		ft_probel2(char **str_map, int stroka, int stolbez);
void	ft_were_player(t_data_game *data_game, int i, int j);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
void	ft_free(t_data_game *data_game);
int		key_press(int key, t_data_game *data_game);
int		key_release(int key, t_data_game *data_game);
int		main_loop(t_data_game *data_game);
void	calc(t_data_game *data_game);
void	draw(t_data_game *data_game);
void	key_update(t_data_game *data_game, t_conf *conf);
void	sortSprites(int *order, double *dist, int amount);
void	sort_order(t_pair *orders, int amount);
void	floor_casting(t_data_game *data_game);
void	wall_casting(t_data_game *data_game);
int		end_game(t_data_game *data_game);
void	sprite_casting_old(t_data_game *data_game);
void	ft_init_wall(t_data_game *data_game, t_wall *wall, int x);
void	ft_init_stap(t_data_game *data_game, t_wall *wall);
void	ft_DDA(t_data_game *data_game, t_wall *wall);
void	ft_drow_wall(t_data_game *data_game, t_wall *wall);
void	ft_calc_stripe(t_data_game *data_game, t_wall *wall);
void	ft_drow_wall2(t_data_game *data_game, t_wall *wall, int x, int y);
char	**ft_malloc_map(char *str_map, int i);
int		ft_malloc_str(t_data_game *data_game, char *str_map, int i);
void	wall_casting_sprite(t_data_game *data_game);
int		ft_inc(t_data_game *data_game, int i, int j);
void	ft_mal_sprite(t_data_game *d_g, t_sp_help *help);
void	ft_kek(t_data_game *data_game, long x_width, long y_height);
int		ft_malloc_buf(t_data_game *data_game);
void	ft_init_conf(t_data_game *data_game);
int		ft_malloc_tex(t_data_game *data_game, int i, int j);
int		screenshot(t_data_game *d_g);
void	screenshot2(int fd, t_data_game *d_g);
void	ft_init_r(long *x_width, long *y_height, int *i);

#endif
