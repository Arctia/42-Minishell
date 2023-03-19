/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:58:31 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/19 14:56:44 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	removable(const char *set, char s)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	size_t	s;
	size_t	e;
	size_t	i;

	s = 0;
	if (!s1)
		return (NULL);
	while (s1[s] && removable(set, s1[s]))
		s++;
	e = ft_strlen(s1);
	while (e > s && removable(set, s1[e - 1]))
		e--;
	str = ft_calloc(sizeof(char), e - s + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (s < e)
		str[i++] = s1[s++];
	str[i] = 0;
	return (str);
}
