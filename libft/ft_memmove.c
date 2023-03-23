/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:13:01 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 10:47:08 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *des, const void *src, size_t len)
{
	int	i;

	if (!des && !src)
		return (NULL);
	if (des > src)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			*(char *)(des + i) = *(char *)(src + i);
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)len)
		{
			*(char *)(des + i) = *(char *)(src + i);
			i++;
		}
	}
	return (des);
}
