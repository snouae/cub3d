SRCS = main.c

OBJS = $(SRCS:%.c=%.o)

NAME = cub3d

HEADER = ./cub3d.h

LIBFT = ./libft

MINILIBX = ./minilibx

LIB = $(LIBFT)/libft.a

MLX = $(MINILIBX)/libmlx.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(LIB) $(HEADER) 
	$(CC) $(CFLAGS) $(LIB) $(MLX) $(OBJS) -lm -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(LIB):
	@make -C libft

$(MLX):
	@make -C minilibx

%.o: %.c	$(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ./*.o $(LIBFT)/*.o  $(MINILIBX)/*.o

fclean:	clean
		rm -rf $(NAME) $(LIB) $(MLX)

re:	fclean all