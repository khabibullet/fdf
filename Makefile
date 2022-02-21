# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 21:25:23 by anemesis          #+#    #+#              #
#    Updated: 2022/02/21 20:53:24 by anemesis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -c -Wall -Wextra -Werror

NAME = libfdf.a

SOURCE =	src/ft_putchar.c	src/ft_putstr.c		src/ft_putnbr.c\
			src/ft_puthex.c		src/ft_putuint.c	src/ft_putptr.c\
			src/ft_printf.c		src/get_next_line.c	src/get_next_line_utils.c\
			src/ft_atoi.c		src/ft_isdigit.c	src/ft_split.c\
			src/ft_strlcpy.c

OBJECTS = $(patsubst %.c, %.o, $(SOURCE))

HEADER = fdf_lib.h

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