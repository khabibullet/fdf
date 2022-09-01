/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:37:55 by anemesis          #+#    #+#             */
/*   Updated: 2022/09/01 18:38:13 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fdf_lib.h"

void	get_parsed(float ****v1p, float ****v2p, int *msize, char *mapname)
{
	char	*str;
	char	**spl;
	int		fd;
	int		h;

	get_map_size(msize, mapname);
	malloc_vectors(v1p, v2p, msize[0], msize[1]);
	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		exit (EXIT_FAILURE);
	h = 0;
	while (h < msize[0])
	{
		str = get_next_line(fd);
		spl = ft_split(str, ' ');
		free(str);
		str_to_int(spl, *v1p, h, msize);
		h++;
	}
	get_centered_inv((*v1p)[2], msize);
	close(fd);
}
