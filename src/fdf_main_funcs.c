/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:49:58 by anemesis          #+#    #+#             */
/*   Updated: 2022/03/07 22:28:14 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

void	draw_map(t_mlx	*gen)
{
	put_white_back(&gen->pic, gen->mlx, gen->wsize);
	if (gen->proj_type == 0)
		get_persp_projection(gen->v1, gen->foc, gen->wsize, gen->msize);
	else
		get_isomet_projection(gen->v1, gen->foc, gen->wsize, gen->msize);
	put_horiz_lines(&gen->pic, gen->v1, gen->wsize, gen->msize);
	put_vertic_lines(&gen->pic, gen->v1, gen->wsize, gen->msize);
	mlx_put_image_to_window(gen->mlx, gen->win, gen->pic.img, 0, 0);
	mlx_destroy_image(gen->mlx, gen->pic.img);
}

int	main_loop(t_mlx	*gen)
{
	get_rot_matrix(gen->rot, gen->angles);
	rotate_cam(gen->v2, gen->v1, gen->msize, gen->rot);
	move_cam(gen, gen->shift, gen->msize, gen->rot);
	draw_map(gen);
	return (0);
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
	get_centered_inv((*v1p)[2], msize);
	close(fd);
}

void	print_grid(float **a, int *msize)
{
	int	h;
	int	w;

	h = 0;
	while (h < msize[0])
	{
		w = 0;
		while (w < msize[1])
		{
			ft_printf("%d.%d%d ", (int)a[h][w],
				(int)(a[h][w] * 100) % 10, (int)(a[h][w] * 10) % 10);
			w++;
		}
		ft_printf("\n");
		h++;
	}
}

void	set_defaults(t_mlx *gen)
{
	gen->foc = gen->wsize[1] / tanf(60 * M_PI / 180 / 2) / 2;
	gen->mouse_sens = 0.5;
	gen->shift_sens = sqrt(powf(gen->msize[0], 2)
			+ powf(gen->msize[1], 2)) / 100;
	get_rot_matrix(gen->rot, (float [2]){0});
	move_cam(gen, (float [2]){0}, gen->msize, gen->rot);
	reset_cam_pos(gen);
}
