SRCS = main.c

OBJS = $(SRCS:%.c=%.o)

NAME = cub3d

HEADER = ./cub3d.h

LIBFT = ./libft

LIB = $(LIBFT)/libft.a


CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(LIB) $(HEADER) 
	$(CC) $(CFLAGS) $(LIB) $(OBJS) -lm -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(LIB):
	@make -C libft

%.o: %.c	$(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf ./*.o $(LIBFT)/*.o

fclean:	clean
		rm -rf $(NAME) $(LIB)

re:	fclean all