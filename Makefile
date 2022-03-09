# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 21:25:23 by anemesis          #+#    #+#              #
#    Updated: 2022/03/09 14:07:00 by anemesis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = libfdf.a

SOURCE =	src/ft_putchar.c		src/ft_putstr.c			src/ft_putnbr.c\
			src/ft_puthex.c			src/ft_putuint.c		src/ft_putptr.c\
			src/ft_atoi.c			src/ft_isdigit.c		src/ft_split.c\
			src/ft_printf.c			src/ft_strlcpy.c\
			src/get_next_line.c		src/get_next_line_utils.c\
			src/fdf_parse.c			src/fdf_transform.c		src/fdf_interact.c\
			src/fdf_draw.c			src/fdf_crop.c			src/fdf_main_funcs.c\
			src/fdf_putpix.c		src/fdf_cam.c\

OBJECTS = $(patsubst %.c, %.o, $(SOURCE))

HEADER = fdf_lib.h

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	ar -rcs $(NAME) $?

%.o: %.c 
	$(CC) -c $(FLAGS) $< -o $@

bonus: $(NAME)
	
clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re