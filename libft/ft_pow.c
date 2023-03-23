/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:13:37 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 11:10:18 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_pow(int num, int n)
{
	long	res;

	if (num == 0)
		return (0);
	if (n == 0)
		return (1);
	res = num;
	n--;
	while (n-- > 0)
		res = res * num;
	return (res);
}
