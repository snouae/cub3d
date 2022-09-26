# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snouae <snouae@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 17:52:47 by snouae            #+#    #+#              #
#    Updated: 2022/09/25 14:48:35 by snouae           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c parser/ft_tools.c parser/get_next_line.c parser/get_next_line_utils.c parser/ft_split.c parser/ft_check_map.c parser/ft_check_paths.c parser/ft_cherch.c parser/ft_read.c
CC = gcc
FLAGS = 
MLXFLAGS = -lmlx -framework OpenGL -framework Appkit
RM = rm  -rf

OBJ= $(SRC:.c=.o)

NAME = cub3d

all : $(NAME) clean

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)

%.o : %.c so_long.h
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re : fclean all

.PHONY:all clean fclean re