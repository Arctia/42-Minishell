/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:16:19 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:16:21 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	strdiff(const char *s1, const char *s2, int *con, int *diff)
{
	*diff = 0;
	if (s1[con[0]] != s2[con[1]])
	{
		*diff = ((unsigned char)(s1[con[0]]) - (unsigned char)(s2[con[1]]));
		return (*diff);
	}
	con[0] += 1;
	con[1] += 1;
	return (0);
}

int	ft_strrncmp(const char *s1, const char *s2, int n)
{
	int		con[2];
	int		diff;

	con[1] = 0;
	while (s2[con[1]])
	{
		diff = 1;
		con[0] = 0;
		while (s1[con[0]] != s2[con[1]] && s2[con[1]])
			con[1]++;
		if (!s2[con[1]])
			break ;
		while (con[0] < n)
		{
			if (strdiff(s1, s2, con, &diff))
				break ;
		}
		if (diff == 0)
			break ;
	}
	return (diff);
}
