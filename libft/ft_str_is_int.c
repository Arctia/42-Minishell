/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:14:30 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 11:10:23 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_is_int(const char *str)
{
	long	num;

	num = ft_atol(str);
	if (num > MAXINT || num < MININT)
		return (0);
	if (ft_issign(str[0]))
		str++;
	while (str++[0])
	{
		if (!ft_isdigit(str[-1]))
			return (0);
	}
	return (1);
}
