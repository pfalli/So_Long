NAME = libtfull.a

# Directories
INC = inc/
SRC_DIR = src/
OBJ_DIR = obj/

# compilers and flags
CC = gcc
FLAGS = -Wall -Werror -Wextra -I$(INC)

# src directories
LIBFT_DIR = $(SRC_DIR)ft_isalpha.c 		$(SRC_DIR)ft_memmove.c 		$(SRC_DIR)ft_strjoin.c \
            $(SRC_DIR)ft_isdigit.c 		$(SRC_DIR)ft_memchr.c 		$(SRC_DIR)ft_strtrim.c \
            $(SRC_DIR)ft_isalnum.c 		$(SRC_DIR)ft_strnstr.c 		$(SRC_DIR)ft_itoa.c \
            $(SRC_DIR)ft_isascii.c 		$(SRC_DIR)ft_strrchr.c 		$(SRC_DIR)ft_strmapi.c \
            $(SRC_DIR)ft_isprint.c 		$(SRC_DIR)ft_strchr.c 		$(SRC_DIR)ft_striteri.c \
            $(SRC_DIR)ft_strlen.c 		$(SRC_DIR)ft_strncmp.c		$(SRC_DIR)ft_striteri.c \
            $(SRC_DIR)ft_memset.c 		$(SRC_DIR)ft_memcmp.c 		$(SRC_DIR)ft_putchar_fd.c \
            $(SRC_DIR)ft_bzero.c 		$(SRC_DIR)ft_tolower.c 		$(SRC_DIR)ft_putstr_fd.c \
            $(SRC_DIR)ft_memcpy.c 		$(SRC_DIR)ft_toupper.c 		$(SRC_DIR)ft_putendl_fd.c \
            $(SRC_DIR)ft_strlen.c 		$(SRC_DIR)ft_atoi.c		 	$(SRC_DIR)ft_split.c \
            $(SRC_DIR)ft_strlcpy.c 		$(SRC_DIR)ft_calloc.c 		$(SRC_DIR)ft_substr.c \
            $(SRC_DIR)ft_strlcat.c 		$(SRC_DIR)ft_strdup.c

PRINTF_DIR = $(SRC_DIR)ft_printf.c $(SRC_DIR)ft_print_char.c $(SRC_DIR)ft_print_hexa.c \
             $(SRC_DIR)ft_print_nbr.c $(SRC_DIR)ft_print_percentage.c $(SRC_DIR)ft_print_ptr.c \
             $(SRC_DIR)ft_print_string.c $(SRC_DIR)ft_print_u.c $(SRC_DIR)ft_print_uphexa.c

GNL_DIR = $(SRC_DIR)get_next_line.c $(SRC_DIR)get_next_line_utils.c


#-----------------------------------------------------------------
SRC = $(LIBFT_DIR) $(PRINTF_DIR) $(GNL_DIR)

OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# build rules make	
all:	$(NAME)

$(NAME):	$(OBJ)
				ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)%.o:	$(SRC_DIR)%
			mkdir	-p	$(@D)
    		$(CC)	$(FLAGS)	-c	$<	-o	$@

clean:
				rm -f $(OBJ_DIR)

fclean: 		clean
				rm -f $(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re