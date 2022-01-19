/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:04:09 by anemesis          #+#    #+#             */
/*   Updated: 2022/01/17 18:17:15 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_lib.h"
#include "src/ft_putchar.c"
#include "src/ft_putstr.c"
#include "src/get_next_line.c"
#include "src/get_next_line_utils.c"

void	my_mlx_pixel_put(t_mlx *var, int x, int y, int color)
{
	char	*dst;

	dst = var->addr + (y * var->line_len + x * (var->bits_per_pix / 8));
	*(unsigned int *)dst = color;
}

int	get_map_size(t_mlx *var)
{
	char	*buf;
	char	*ptr;
	int		flag;

	var->map_fd = open(var->map_name, O_RDONLY);
	if (var->map_fd < 0)
	{
		perror("Map error");
		return (1);
	}
	flag = 0;
	var->map_h = 0;
	var->map_w = 0;
	buf = get_next_line(var->map_fd);
	while (buf)
	{
		if (flag == 0)
		{
			ptr = buf;
			while (*buf)
			{
				if (ft_isdigit(*buf) && (*(buf + 1) == ' '
						|| !(*(buf + 1)) || *(buf + 1) == '\n'))
					var->map_w++;
				buf++;
			}
			buf = ptr;
			flag = 1;
		}
		var->map_h++;
		free(buf);
		buf = get_next_line(var->map_fd);
	}
	close(var->map_fd);
	return (0);
}

int	parse_map(t_mlx *var)
{
	char	*str;
	char	**spl;

	if (get_map_size(var))
		return (1);
	var->map_fd = open(var->map_name, O_RDONLY);
	var->map = malloc(sizeof(*var->map) * var->map_h);
	if (!var->map)
		return (1);
	str = get_next_line(var->map_fd);
	while (str)
	{
		spl = ft_split(str, ' ');
		free(str);
		*var->map = malloc(sizeof(**var->map) * var->map_w);
		if (!*var->map)
			return (1);
		while (*spl)
		{
			**var->map = ft_atoi(*spl);
			free(*spl);
			spl++;
			(*var->map)++;
		}
		*var->map = *var->map - var->map_w;
		(var->map)++;
		spl = spl - var->map_w;
		free(spl);
		str = get_next_line(var->map_fd);
	}
	var->map = var->map - var->map_h;
	close(var->map_fd);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_mlx	var;

	if (argc != 2)
	{
		ft_putstr("Error. No input map\n");
		return (0);
	}
	var.map_name = argv[1];
	if (parse_map(&var) == 1)
		return (1);
	var.win_h = 500;
	var.win_w = 500;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, var.win_w, var.win_h, "Hello world!");
	var.img = mlx_new_image(var.mlx, var.win_w, var.win_h);
	var.addr = mlx_get_data_addr(var.img, &var.bits_per_pix, &var.line_len, &var.endian);
	var.y_pix = 0;
	while (var.y_pix < var.win_w)
	{
		var.x_pix = 0;
		while (var.x_pix < var.win_h)
		{
			my_mlx_pixel_put(&var, var.x_pix, var.y_pix, 0x00ffffff);
			var.x_pix++;
		}
		var.y_pix++;
	}
	mlx_put_image_to_window(var.mlx, var.win, var.img, 0, 0);
	// mlx_loop(var.mlx);
	while 
	return (0);
}
