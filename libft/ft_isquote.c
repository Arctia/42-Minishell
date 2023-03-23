/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:09:41 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 11:10:25 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* if char is a quote return it's value, else return null character */
char	ft_isquote(char ch)
{
	if (ch == '\'' || ch == '"')
		return (ch);
	return ('\0');
}
