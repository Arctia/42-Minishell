/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmatrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:02:14 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/19 14:25:57 by vgavioli         ###   ########.fr       */
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
