# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 21:25:23 by anemesis          #+#    #+#              #
#    Updated: 2022/01/11 22:58:42 by anemesis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -c -Wall -Wextra -Werror

NAME = fdf

SOURCE =	ft_putchar.c	ft_putstr.c		ft_putnbr.c\
			ft_puthex.c		ft_putuint.c	ft_putptr.c\
			ft_printf.c\
			get_next_line.c	get_next_line_utils.c\

OBJECTS = $(patsubst %.c, %.o, $(SOURCE))

HEADER = ft_printf.h

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	ar -rcs $(NAME) $?

%.o: %.c 
	$(CC) $(CFLAGS) $< -o $@

bonus: $(NAME)
	
clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re