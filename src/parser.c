/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:25:17 by anemesis          #+#    #+#             */
/*   Updated: 2022/03/02 16:28:33 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

void	count_size(int fd, int	*msize)
{
	int		flag;
	char	*buf;
	char	*ptr;

	flag = 0;
	buf = get_next_line(fd);
	while (buf)
	{
		if (flag == 0)
		{
			ptr = buf;
			while (*buf)
			{
				if (ft_isdigit(*buf) && (*(buf + 1) == ' '
						|| !(*(buf + 1)) || *(buf + 1) == '\n'))
					msize[1]++;
				buf++;
			}
			buf = ptr;
			flag = 1;
		}
		msize[0]++;
		free(buf);
		buf = get_next_line(fd);
	}
}

void	get_map_size(int	*msize, char	*mapname)
{
	int	fd;

	fd = open(mapname, O_RDONLY);
	if (fd < 0)
	{
		perror("Map error");
		exit (EXIT_FAILURE);
	}
	msize[0] = 0;
	msize[1] = 0;
	count_size(fd, msize);
	close(fd);
}

void	str_to_int(char **spl, float ***v1, int h, int *msize)
{
	int		w;
	float	xoffs;
	float	yoffs;

	xoffs = (float)(msize[1] - 1) / 2;
	yoffs = (float)(msize[0] - 1) / 2;
	w = 0;
	while (spl[w])
	{
		v1[0][h][w] = (float)w - xoffs;
		v1[1][h][w] = (float)h - yoffs;
		v1[2][h][w] = (float)ft_atoi(spl[w]);
		free(spl[w]);
		w++;
	}
	free(spl);
}

void	malloc_vectors(float ****v1p, float ****v2p, int h, int w)
{
	int	y;
	int	d;

	*v1p = malloc(sizeof(**v1p) * 3);
	*v2p = malloc(sizeof(**v2p) * 3);
	if (!(*v1p) || !(*v2p))
		exit (EXIT_FAILURE);
	d = 0;
	while (d < 3)
	{
		y = 0;
		(*v1p)[d] = malloc(sizeof(***v1p) * h);
		(*v2p)[d] = malloc(sizeof(***v2p) * h);
		if (!(*v1p)[d] || !(*v2p)[d])
			exit (EXIT_FAILURE);
		while (y < h)
		{
			(*v1p)[d][y] = malloc(sizeof(****v1p) * w);
			(*v2p)[d][y] = malloc(sizeof(****v2p) * w);
			if (!(*v1p)[d][y] || !(*v2p)[d][y])
				exit (EXIT_FAILURE);
			y++;
		}
		d++;
	}
}

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
	close(fd);
}
