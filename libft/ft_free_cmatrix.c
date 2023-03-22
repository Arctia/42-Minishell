/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmatrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:08:43 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:08:45 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_cmatrix(char **mtx)
{
	int	i;

	i = -1;
	if (mtx)
	{
		while (mtx[++i] && mtx[i][0])
			free(mtx[i]);
		free(mtx);
	}
}

void	ft_free_imatrix(int **mtx)
{
	int	i;

	i = 0;
	if (mtx)
	{
		while (mtx[i])
			free(mtx[i++]);
		free(mtx);
	}
}
