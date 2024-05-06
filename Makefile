NAME = so_long

INC = ./inc/
LIBFT = ./libft_full/libft.a
LIBFT_PATH = ./libft_full

SRC =$(addprefix src/, so_long.c \
								utils_controls.c \
								utils_draw.c \
								utils_free.c \
								utils_map.c \
								utils_mapcheck.c \
								utils.c )

OBJ = $(SRC:.c=.o)

CC = gcc
CCFLAGS = -Wall -Werror -Wextra -g -I$(INC)
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

MLX_DIR = ./minilibx
MLX = ./minilibx/libmlx.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	$(CC) $(CCFLAGS) $(MLX_FLAGS)  -o $(NAME) $(SRC) $(LIBFT) $(MLX)
# now libft works

$(OBJ): $(SRC)
	@mkdir -p $(@D)
	$(CC) -c $(CCFLAGS) -o $@ $<
# now  the .o files are inside src

start:
	make all

libft:
	make -C $(LIBFT_PATH)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re : fclean all

# gcc so_long.c -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
# gcc -Wall -Wextra -Werror -g so_long.c -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
# valgrind --leak-check=full --show-leak-kinds=all