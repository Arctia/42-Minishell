/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:25:18 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 10:47:09 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *des, const void *src, size_t n)
{
	size_t	i;

	if (des == src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(char *)(des + i) = *(const char *)(src + i);
		i++;
	}
	return (des);
}
