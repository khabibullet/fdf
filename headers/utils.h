/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:25:42 by anemesis          #+#    #+#             */
/*   Updated: 2022/09/01 20:24:40 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# define BUFFER_SIZE 256
# include "sys/types.h"
# include <stdlib.h>

typedef struct s_var
{
	char		buf[BUFFER_SIZE + 1];
	ssize_t		red;
	char		*line;
	int			err_flag;
}	t_var;

typedef struct s_mlx	t_mlx;

char	*get_next_line(int fd);
void	*safe_malloc(size_t size);
void	exit_error(char *str);
void	exit_fdf(t_mlx *gen);

#endif
