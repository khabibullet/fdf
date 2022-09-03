/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:37:55 by anemesis          #+#    #+#             */
/*   Updated: 2022/09/03 20:54:05 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fdf.h"

static void	check_num_of_args(int argc)
{
	if (argc != 2)
	{
		write(1, "Map error: Invalid arguments\n", 30);
		exit(EXIT_FAILURE);
	}
}

void	get_parsed(int argc, t_mlx *gen, char *mapname)
{
	char	*str;
	char	**spl;
	int		fd;
	int		h;

	check_num_of_args(argc);
	get_map_size(gen->msize, mapname);
	malloc_vectors(&gen->v1, &gen->v2, gen->msize[0], gen->msize[1]);
	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	h = 0;
	while (h < gen->msize[0])
	{
		str = get_next_line(fd);
		spl = ft_split(str, ' ');
		free(str);
		str_to_int(spl, gen->v1, h, gen->msize);
		h++;
	}
	get_centered_inv((gen->v1)[2], gen->msize);
	close(fd);
}
