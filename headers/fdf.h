/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:08:20 by anemesis          #+#    #+#             */
/*   Updated: 2022/09/03 12:24:47 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_LIB_H
# define FDF_LIB_H
# define BUFFER_SIZE 256
# define HEIGHT 0
# define WIDTH 1
# include "../libraries/libmlx/headers/mlx.h"
# include "../libraries/libft/libft.h"
# include "utils.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <stdarg.h>

# define KEY_Q		12
# define KEY_W		13
# define KEY_E		14
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_O		31
# define KEY_R		15
# define KEY_P		35
# define KEY_ESC	53
# define KEY_PLUS	24
# define KEY_MINUS	27

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_MOUSE_MOVE		6
# define X_EVENT_EXIT			17

typedef struct s_img
{
	void	*img;
	int		depth;
	int		len;
	int		end;
	char	*addr;
}	t_img;

typedef struct s_line
{
	float	x1;
	float	y1;
	float	x2;
	float	y2;
	int		sgn;
	int		flag;
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	err;
	float	ycur;
}	t_line;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	float			foc;
	float			shift[3];
	float			rot[3][3];
	float			angles[2];
	int				wsize[2];
	int				msize[2];
	float			***v1;
	float			***v2;
	float			mouse_sens;
	float			shift_sens;
	int				proj_type;
	struct s_img	pic;
	struct s_img	hint;
	struct s_line	ln;
}	t_mlx;

/**	
** parsing
**/

void	count_size(int fd, int	*msize);
void	get_map_size(int	*msize, char	*mapname);
void	str_to_int(char **spl, float ***v1, int h, int *msize);
void	malloc_vectors(float ****v1p, float ****v2p, int h, int w);
void	get_centered_inv(float **x, int *msize);
void	get_parsed(int argc, t_mlx *gen, char *mapname);

void	initialize_fdf(t_mlx *gen);

/**	
**		movement
**/

void	get_transposed(float rot[3][3]);
void	get_rot_matrix(float rot[3][3], float *angles);
void	rotate_cam(float ***v1, float ***v2, int *msize, float rot[3][3]);
void	get_shifted(float ***v1, float *shift, int	*msize);
void	move_cam(t_mlx	*gen, float *shift, int *msize, float rot[3][3]);
void	reset_cam_pos(t_mlx *gen);
void	get_centered(float **z, int *msize);
void	change_proj(int *proj_type);

/**	
**		handling
**/

int		mouse_hook(int x2, int y2, t_mlx *gen);
int		key_press(int keycode, t_mlx *gen);
int		key_release(int keycode, t_mlx *gen);
int		exit_hook(t_mlx *gen);
void	limit_shift(t_mlx *gen);

/**	
**		drawing
**/

int		main_loop(t_mlx	*gen);
void	draw_map(t_mlx	*gen);
void	put_white_back(t_img *pic, int *wsize);
void	get_isomet_projection(float ***v1, float foc, int *wsize, int *msize);
void	get_persp_projection(float ***v1, float foc, int *wsize, int *msize);
void	put_vertic_lines(t_img *pic, float ***v1, int *wsize, int *msize);
void	put_horiz_lines(t_img *pic, float ***v1, int *wsize, int *msize);
void	my_mlx_pixel_put(t_img *pic, int x, int y, unsigned int color);
void	put_pixels_wu(t_img *pic, t_line ln);
void	swap_pairs(float *a1, float *a2, float *b1, float *b2);
void	swap_points(t_line	*ln, float xx_yy[4]);
void	put_line(t_img	*pic, float xx_yy[4]);
float	get_min(float **z, int *msize);
float	get_max(float **z, int *msize);
int		crop_line(float xx_yy[4], int *wsize);
void	crop_y(float xx_yy[4], float k, int fl, int *wsize);
float	crop_x(float xx_yy[4], int *wsize);

#endif
