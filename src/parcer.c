/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:25:17 by anemesis          #+#    #+#             */
/*   Updated: 2022/02/22 19:29:18 by anemesis         ###   ########.fr       */
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

int	get_map_size(int	*msize, char	*mapname)
{
	int	fd;

	fd = open(mapname, O_RDONLY);
	if (fd < 0)
	{
		perror("Map error");
		return (1);
	}
	msize[0] = 0;
	msize[1] = 0;
	count_size(fd, msize);
	close(fd);
	return (0);
}

int	*str_to_int(char **spl, int **map, int i, int *msize)
{
	int	j;

	map[i] = malloc(sizeof(*map) * msize[1]);
	if (!map[i])
		return (NULL);
	j = 0;
	while (spl[j])
	{
		map[i][j] = ft_atoi(spl[j]);
		free(spl[j]);
		j++;
	}
	free(spl);
	return (map[i]);
}

int	**parse_map(t_mlx	*gen, int	**map, int	*msize, char	*mapname)
{
	char	*str;
	char	**spl;
	int		fd;
	int		i;

	if (get_map_size(msize, mapname))
		return (NULL);
	fd = open(mapname, O_RDONLY);
	map = malloc(sizeof(*map) * msize[0]);
	if (!map)
		return (NULL);
	i = 0;
	while (i < msize[0])
	{
		str = get_next_line(fd);
		spl = ft_split(str, ' ');
		free(str);
		map[i] = str_to_int(spl, map, i, msize);
		if (!map[i])
			return (NULL);
		i++;
	}
	close(fd);
	gen->map = map;
	return (map);
}

void	print_array(int	**arr, int h, int w)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < h)
	{
		x = 0;
		c = ' ';
		while (x < w)
		{
			if (x == w - 1)
				c = '\n';
			ft_printf("%d%c", (int)arr[y][x], c);
			x++;
		}
		y++;
	}
}
