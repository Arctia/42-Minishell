/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:15:42 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:15:44 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	c;
	size_t	h;

	c = 0;
	h = 0;
	while (src[h])
		h++;
	while (c < (dstsize - 1) && src[c] && dstsize != 0)
	{
		dst[c] = src[c];
		c++;
	}
	if (dstsize != 0)
		dst[c] = 0;
	return (h);
}
