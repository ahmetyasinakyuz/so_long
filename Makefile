# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aakyuz <aakyuz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 18:22:28 by aakyuz            #+#    #+#              #
#    Updated: 2024/12/16 12:27:49 by aakyuz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	so_long

SRC	=		ft_printf/ft_hex.c\
			ft_printf/ft_printf.c\
			ft_printf/ft_putchar.c\
			ft_printf/ft_puthex.c\
			ft_printf/ft_putnbr.c\
			ft_printf/ft_putptr.c\
			ft_printf/ft_putstr.c\
			ft_printf/ft_putuint.c\
			find.c\
			game.c\
			get_next_line_utils.c\
			get_next_line.c\
			images.c\
			map_checker_1.c\
			map_checker_2.c\
			so_long.c\

OBJS = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
AR = ar crs


all: $(NAME)

$(NAME): $(OBJS)
	@make -C minilibx-linux/
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./minilibx-linux/libmlx.a -lX11 -lXext -lm
	@echo "Compilation done"

clean:
	@make clean -C minilibx-linux/
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
