NAME 			= cub3D

FLAGS 			= -Wall -Werror -Wextra

PARSER_PATH 	= srcs/
RAYCAST_PATH 	= raycast/

FILES			= cub3D.c cub3d_p2.c cub3d_p3.c
PARSER_FILES 	= chek_map_p1.c chek_map_p2.c chek_map_p3.c chek_map.c libft.c chek_map_p22.c help_init.c
RAYCAST_FILES	= key_press.c main_raycast.c floor.c wall.c sprite_new.c wall2.c

PARSER_SRCS 	= $(addprefix $(PARSER_PATH), $(PARSER_FILES))
RAYCAST_SRCS 	= $(addprefix $(RAYCAST_PATH), $(RAYCAST_FILES))

LIBS			= -lmlx -framework OpenGL -framework AppKit -lm
MLX				= ./minilibx_opengl_20191021/libmlx.a

OBJS			= $(FILES:.c=.o)
PARSER_OBJS 	= $(PARSER_SRCS:.c=.o)
RAYCAST_OBJS	= $(RAYCAST_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(PARSER_OBJS) $(RAYCAST_OBJS) $(MLX)
		gcc $(FLAGS) -o $(NAME) $(PARSER_OBJS) $(RAYCAST_OBJS) $(OBJS) $(LIBS)

$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .

clean:
	@rm -rf $(OBJS)
	@rm -rf $(PARSER_OBJS)
	@rm -rf $(RAYCAST_OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

