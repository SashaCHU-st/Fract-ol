NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES = main.c
			
			
OBJ = ${SOURCES:.c=.o}

#Minilibx
# MLX_PATH	= minilibx_mms_20191025_beta/
# MLX_NAME	= libmlx.a
# MLX			= $(MLX_PATH)$(MLX_NAME)

#Libft
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@
$(LIBFT):
	make -C $(LIBFT_PATH) all

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re