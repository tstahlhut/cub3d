NAME = cub3D
CC = cc
CFLAGS = -g -Wall -Wextra -Werror 
MLXFLAGS = -L ../../minilibx-linux -lm -lmlx -lXext -lX11 
DEPS = ../../minilibx-linux/mlx.h libs/libft/libft.a

DIRSRC = ./src/

C_FILES = main init exit window event_handling \
			init_map init_map_utils map_check textures \
			render_map move_player raycasting raycasting_calc \
			utils timer init_map_utils2 map_check_utils map_check_utils2 \
			move_player_utils render_map_utils

SRC = ${addprefix ${DIRSRC}, $(addsuffix .c, $(C_FILES))}
OBJ = $(SRC:.c=.o)

LIBFT = libs/libft/libft.a

all: libs $(NAME)

$(LIBFT):
	$(MAKE) -C ./libs/libft

libs:
	$(MAKE) -C ../../minilibx-linux
	
$(NAME): $(OBJ) $(libs) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)


clean:
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(OBJ)

fclean: clean
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(NAME)

re: fclean all
	$(MAKE) re -C ./libs/libft
	

r: fclean all
	./$(NAME) "maps/map.cub"

gdb: fclean all
	gdb $(NAME) "maps/map.cub"
v: fclean all
	 valgrind --leak-check=full ./$(NAME) "maps/map.cub" 
vv:fclean all
	valgrind --leak-check=full ./$(NAME) "maps/bad/wall_none.cub"
.PHONY: all clean fclean re