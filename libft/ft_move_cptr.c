/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_cptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:13:30 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 10:47:11 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_move_cptr(char **str)
{
	if (*str[0])
		(*str)++;
}

void	ft_move_n_cptr(char **str, size_t n)
{
	while (n-- > 0)
		ft_move_cptr(str);
}

// retrieve ptr position
char	**ft_reset_cptr(char **str, int status)
{
	static char	**ptr;

	if (status == 1 && ptr)
		return (ptr);
	ptr = str;
	return (NULL);
}

// store ptr position
void	ft_init_cptr(char **str)
{
	ft_reset_cptr(str, 0);
}
