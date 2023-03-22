/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_i_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:08:21 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:08:24 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// if str > MAXINT or < MININT, undefined behaviour
int	*ft_fill_i_array(char **mat, long size)
{
	int	*array;
	int	i;

	array = (int *)malloc(sizeof(int) * (size + 1));
	if (!array)
		return (NULL);
	i = -1;
	while (mat[++i])
		array[i] = ft_atol(mat[i]);
	array[i] = '\0';
	return (array);
}
