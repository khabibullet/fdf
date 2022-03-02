/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_lib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:08:20 by anemesis          #+#    #+#             */
/*   Updated: 2022/02/28 19:08:45 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_LIB_H
# define FDF_LIB_H
# define BUFFER_SIZE 256
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <stdarg.h>

typedef struct t_var
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	red;
	char	*line;
	int		err_flag;
}	t_var;

typedef struct t_img
{
	void	*img;
	int		depth;
	int		len;
	int		end;
	char	*addr;
}	t_img;

typedef struct t_line
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

typedef struct t_mlx
{
	void			*mlx;
	void			*win;
	float			focal;
	float			shift[3];
	float			rot[3][3];
	float			angles[2]; // [fi, teta] in degrees
	int				wsize[2]; // window [height, width]
	int				msize[2]; // map [height, width]
	float			***v1;
	float			***v2;
	struct t_img	pic;
	struct t_line	ln;
}	t_mlx;

/**
** get_next_line functions
**/
char	*get_next_line(int fd);
char	*ft_strjoin(char	*s1, char	*s2);

/**	
** libft/utils functions
**/
size_t	ft_strlcpy(char	*dst, const char	*src, size_t	dstsize);
size_t	ft_strlen(const char	*str);
size_t	ft_strlcat(char	*dest, const char	*src, size_t	destsize);
char	*ft_strchr(const char	*s, int c);
size_t	ft_strlcpy(char	*dst, const char	*src, size_t	dstsize);
char	**ft_split(char	const	*s, char c);
int		ft_putchar(char c);
int		ft_isdigit(int c);

/**	
** ft_printf functions
**/
int		ft_atoi(const char	*str);
int		ft_printf(const char	*format, ...);
int		ft_putchar(char c);
int		ft_putstr(char	*s);
int		ft_putnbr(int n);
int		ft_puthex(unsigned int n, char specifier);
int		ft_putptr(void *p);
int		ft_putuint(unsigned int n);

/**	
** parser.c functions
**/
void	count_size(int fd, int	*msize);
void	get_map_size(int	*msize, char	*mapname);
void	str_to_int(char **spl, float ***v1, int h, int *msize);
void	malloc_vectors(float ****v1p, float ****v2p, int h, int w);
void	get_parsed(float ****v1p, float ****v2p, int *msize, char *mapname);

/**	
** printer.c functions
**/

void	print_ptr_array(float	**arr, int h, int w);
void	print_3x3_array(float arr[3][3]);

/**	
** transform.c functions
**/

void	get_rot_matrix(float rot[3][3], float *angles);
void	rotate_cam(float ***v1, float ***v2, float *angles, int	*msize);
void	get_shifted(float ***v1, float *shift, int	*msize);
void	move_cam(t_mlx	*gen, float *shift, float *angles, int *msize);

#endif
