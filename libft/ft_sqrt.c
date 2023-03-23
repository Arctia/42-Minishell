/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:14:25 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 11:10:27 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(long num)
{
	int	res;
	int	n;

	n = 0;
	while (n < MAXINT || n > num / 2)
	{
		res = ft_pow(n, 2);
		if (res == num)
			return (res);
		else if (res > num)
			return (-1);
		n++;
	}
	return (-1);
}
