/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_lib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:08:20 by anemesis          #+#    #+#             */
/*   Updated: 2022/01/19 15:45:40 by anemesis         ###   ########.fr       */
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
#include <errno.h>

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
	int		bits_per_pix;
	int		line_len;
	int		end;
	char	*addr;
}	t_img;

typedef struct t_mlx
{
	void			*mlx;
	void			*win;
	int				map_h;
	int				map_w;
	int				win_h;
	int				win_w;
	int				x_pix;
	int				y_pix;
	int				**map;
	char			*map_name;
	int				map_fd;
	struct t_img	pic;

	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				x;
	int				y;
}	t_mlx;

// get_next_line functions
char	*get_next_line(int fd);
char	*ft_strjoin(char	*s1, char	*s2);

// libft functions
size_t	ft_strlcpy(char	*dst, const char	*src, size_t	dstsize);
size_t	ft_strlen(const char	*str);
size_t	ft_strlcat(char	*dest, const char	*src, size_t	destsize);
char	*ft_strchr(const char	*s, int c);
size_t	ft_strlcpy(char	*dst, const char	*src, size_t	dstsize);
char	**ft_split(char	const	*s, char c);
int		ft_putchar(char c);
int		ft_putstr(char	*s);
int		ft_isdigit(int c);

#endif
