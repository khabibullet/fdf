/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:25:45 by anemesis          #+#    #+#             */
/*   Updated: 2022/01/14 21:53:44 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_lib.h"

size_t	ft_strlen(const char	*str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// size_t	ft_strlcpy(char	*dst, const char	*src, size_t	dstsize)
// {
// 	size_t	i;

// 	i = 0;
// 	if (dstsize)
// 	{
// 		while ((i < dstsize - 1) && src[i])
// 		{
// 			dst[i] = src[i];
// 			++i;
// 		}
// 		dst[i] = '\0';
// 	}
// 	while (src[i])
// 		++i;
// 	return (i);
// }

size_t	ft_strlcat(char	*dest, const char	*src, size_t	destsize)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	destlen = 0;
	while (dest[destlen] && destlen < destsize)
		destlen++;
	if (destlen == destsize)
		return (srclen + destsize);
	i = 0;
	while ((destlen + i + 1 < destsize) && src[i])
	{
		dest[destlen + i] = src[i];
		++i;
	}
	dest[destlen + i] = '\0';
	return (srclen + destlen);
}

char	*ft_strjoin(char	*s1, char	*s2)
{
	char	*new;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(new, s1, s1_len + 1);
	ft_strlcat(new, s2, s1_len + s2_len + 1);
	free(s1);
	return (new);
}

char	*ft_strchr(const char	*s, int c)
{
	if (!s)
		return (NULL);
	while (c >= 0)
		c = c - 256;
	c = c + 256;
	while ((*s != c) && (*s != '\0'))
		s++;
	if ((*s == '\0') && (c == '\0'))
		return ((char *)s);
	if (*s == '\0')
		return (NULL);
	return ((char *)s);
}
