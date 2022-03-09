# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 21:25:23 by anemesis          #+#    #+#              #
#    Updated: 2022/03/09 19:19:11 by anemesis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = fdf

HEADER = fdf_lib.h

SOURCE =	ft_putchar.c		ft_putstr.c			ft_putnbr.c\
			ft_puthex.c			ft_putuint.c		ft_putptr.c\
			ft_atoi.c			ft_isdigit.c		ft_split.c\
			ft_printf.c			ft_strlcpy.c\
			get_next_line.c		get_next_line_utils.c\
			fdf_parse.c			fdf_transform.c		fdf_interact.c\
			fdf_draw.c			fdf_crop.c			fdf_main_funcs.c\
			fdf_putpix.c		fdf_cam.c			fdf.c\

OBJECTS = $(patsubst %.c, obj/%.o, $(SOURCE))

all: $(NAME)

$(NAME) : $(OBJECTS) $(HEADER)
	$(CC) $(OBJECTS) -I $(HEADER) $(FLAGS) -lm -lmlx -framework OpenGL -framework AppKit -o $(NAME)

obj/%.o: src/%.c | obj
	$(CC) -c $(FLAGS) $< -o $@

obj:
	mkdir -p obj

bonus: $(NAME)
	
clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus obj