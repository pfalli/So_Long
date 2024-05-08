NAME = so_long

SRC =$(addprefix src/, so_long.c \
								utils_controls.c \
								utils_draw.c \
								utils_free.c \
								utils_map.c \
								utils_mapcheck.c \
								utils_mapcheck2.c \
								utils.c )

CC = cc
CCFLAGS = -Wall -Werror -Wextra -g
MLX_FLAGS = -L/usr/X11/lib -lX11 -lXext -lm

LIBFT = ./libft_full/libft.a
LIBFT_PATH = ./libft_full
MLX_DIR = ./minilibx-linux
MLX = ./minilibx-linux/libmlx.a

all: $(NAME)

$(NAME):
	@make -C $(MLX_DIR)
	@make -C $(LIBFT_PATH)
	$(CC) $(CCFLAGS) $(MLX_FLAGS) -o $(NAME) $(SRC) $(LIBFT) $(MLX)
# now libft works

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re : fclean all

# gcc so_long.c -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
# gcc -Wall -Wextra -Werror -g so_long.c -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11  " ON MY LAPTOP"
# valgrind --leak-check=full --show-leak-kinds=all