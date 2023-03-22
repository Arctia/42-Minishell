/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:07:11 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:07:14 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdup(char **ar)
{
	char	**ret;
	int		i;

	i = 0;
	while (ar[i])
		i++;
	ret = ft_calloc(sizeof(char *), i + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (ar[i])
	{
		ret[i] = ft_strdup(ar[i]);
		if (!ret[i])
		{
			ft_free_cmatrix(ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}
