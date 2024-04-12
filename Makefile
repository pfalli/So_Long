NAME = so_long

LIBFT = ./libft_full/libft.a
LIBFT_PATH = ./libft_full

SRC = $(so_long.c)

OBJ := $(SRC:%.c=%.o)

CC = gcc
CCFLAGS = -Wextra -Wall -Werror

# Contains the X11 and MLX header files
INCLUDES = -I/usr/include -Imlx

MLX_DIR = ./minilibx
MLX_LIB = ./minilibx/libmlx.a

# Link X11 and MLX
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
 

all: $(MLX_LIB) (NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	make clean -C mlx/
	rm -f $(NAME)

re : fclean all



# gcc so_long.c -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11